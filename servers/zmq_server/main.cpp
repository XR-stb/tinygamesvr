#include <grpcpp/generic/generic_stub.h>
#include <grpcpp/grpcpp.h>

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <zmq.hpp>

#include "framework/rpc/base_rpc_object.h"
#include "framework/rpc/rpc_service_registry.h"
#include "helper/singleton.h"
#include "protocol/proto_gen/server/cs_hello.grpc.pb.h"
#include "protocol/proto_gen/server/cs_hello.pb.h"
#include "protocol/proto_gen/server/rpc.pb.h"

namespace PROJ_NS {
class GreeterServiceImpl final : public pb::Greeter::Service, public Singleton<GreeterServiceImpl> {
  DECLARE_SERVICE_METHOD(GreeterServiceImpl, SayHello, CSReqHello, CSResHello, rpc::BaseRpcObject);
};

REG_GRPC_SERVICE(GreeterServiceImpl);
IMPLEMENT_SERVICE_METHOD(GreeterServiceImpl, SayHello) {
  std::string prefix("Hello ");
  response_.set_message(prefix + request_.name());
  std::cout << "SayHello called" << std::endl;
  return 0;
}
}  // namespace PROJ_NS

class RpcServer {
 public:
  std::string HandleRequest(const std::string& request_str) {
    rpc::RpcRequest request;
    request.ParseFromString(request_str);

    grpc::ServerContext context;
    auto it = PROJ_NS::get_factory_map().find(request.method());
    for (auto& e : PROJ_NS::get_factory_map()) {
      std::cout << e.first << std::endl;
    }
    if (it != PROJ_NS::get_factory_map().end()) {
      auto request_message = it->second.first();
      auto response_message = it->second.second();

      request_message->ParseFromString(request.payload());
      grpc::Status status = PROJ_NS::get_rpc_map()[request.method()](
          &context, request_message.get(), response_message.get());

      rpc::RpcResponse response;
      response.set_code(status.error_code());
      response.set_message(status.error_message());
      response.set_payload(response_message->SerializeAsString());

      return response.SerializeAsString();
    }
    std::cout << "un find: " << request.method() << std::endl;
    return "";
  }

  void RunZmqServer() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5555");

    while (true) {
      zmq::message_t request;
      socket.recv(&request);

      std::string request_str(static_cast<char*>(request.data()), request.size());
      std::string response_str = HandleRequest(request_str);

      zmq::message_t response(response_str.size());
      memcpy(response.data(), response_str.data(), response_str.size());
      socket.send(response);
    }
  }

  void RunGrpcServer() {
    std::string server_address("0.0.0.0:50051");

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&PROJ_NS::GreeterServiceImpl::Instance());
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "gRPC Server listening on " << server_address << std::endl;
    server->Wait();
  }
};

int main() {
  RpcServer rpc_server;

  // 启动 ZeroMQ 服务器线程
  std::thread zmq_thread(&RpcServer::RunZmqServer, &rpc_server);

  // 启动 gRPC 服务器线程
  std::thread grpc_thread(&RpcServer::RunGrpcServer, &rpc_server);

  // 等待两个线程完成
  zmq_thread.join();
  grpc_thread.join();

  return 0;
}