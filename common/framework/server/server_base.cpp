#include "server_base.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <zmq.hpp>

#include "common/log/log.h"
#include "framework/rpc/rpc_common.h"
#include "framework/rpc/rpc_service_registry.h"
namespace PROJ_NS {
void ServerBase::Run(std::string svr_name, std::string grpc_port, std::string zmq_port) {
  // 日志最先初始化
  Logger::Instance().init("logs/" + svr_name, "dev", 0, 0);

  MDEBUG("factory_map_size: {}", PROJ_NS::get_factory_map().size());
  for (auto& e : get_factory_map()) {
    MDEBUG("register rpc: {}", e.first);
  }

  // 启动 ZeroMQ 服务器线程
  std::thread zmq_thread(&ServerBase::runZmqServer, this, zmq_port);

  // 启动 gRPC 服务器线程
  std::thread grpc_thread(&ServerBase::runGrpcServer, this, grpc_port,
                          std::ref(GetServiceRegistry()));

  zmq_thread.join();
  grpc_thread.join();
}

std::string ServerBase::handleZmqRequest(const std::string& request_str) {
  rpc::RpcRequest request;
  request.ParseFromString(request_str);

  MDEBUG("factory_map_size: {}", get_factory_map().size());
  for (auto& e : get_factory_map()) {
    MDEBUG("register rpc: {}", e.first);
  }

  grpc::ServerContext context;
  auto it = get_factory_map().find(request.method());

  if (it != get_factory_map().end()) {
    auto request_message = it->second.first();
    auto response_message = it->second.second();

    request_message->ParseFromString(request.payload());
    grpc::Status status =
        get_rpc_map()[request.method()](&context, request_message.get(), response_message.get());

    rpc::RpcResponse response;
    response.set_code(status.error_code());
    response.set_message(status.error_message());
    response.set_payload(response_message->SerializeAsString());

    return response.SerializeAsString();
  }

  MERROR_RETURN("", "method:{} not find", request.method());
}

void ServerBase::runZmqServer(std::string port) {
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_REP);
  socket.bind("tcp://*:" + port);

  while (true) {
    zmq::message_t request;
    auto&& client_socket = socket.recv(request, zmq::recv_flags(0));

    std::string request_str(static_cast<char*>(request.data()), request.size());
    std::string response_str = handleZmqRequest(request_str);

    zmq::message_t response(response_str.size());
    memcpy(response.data(), response_str.data(), response_str.size());
    socket.send(response, zmq::send_flags(0));
  }
}

void ServerBase::runGrpcServer(std::string port, std::set<::grpc::Service*>& services) {
  std::string server_address = "0.0.0.0:" + port;
  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  for (auto&& service : services) {
    builder.RegisterService(service);
  }
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  MINFO("gRPC Server listening on {}", server_address)
  std::cout << "gRPC Server listening on " << server_address << std::endl;

  server->Wait();
}

// void RunServer(uint16_t port, std::set<::grpc::Service*> services, std::string svr_name) {
//   // 日志最先初始化
//   Logger::Instance().init("logs/" + svr_name, "dev", 0, 0);

//   std::string server_address = "0.0.0.0:" + std::to_string(port);
//   grpc::EnableDefaultHealthCheckService(true);
//   grpc::reflection::InitProtoReflectionServerBuilderPlugin();

//   grpc::ServerBuilder builder;
//   builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
//   for (auto&& service : services) {
//     builder.RegisterService(service);
//   }
//   std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

//   std::cout << "Server listening on " << server_address << std::endl;
//   server->Wait();
// }
}  // namespace PROJ_NS