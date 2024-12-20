#include <grpcpp/grpcpp.h>

#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "protocol/proto_gen/server/cs_hello.grpc.pb.h"
#include "protocol/proto_gen/server/cs_hello.pb.h"

using RpcFunc = std::function<grpc::Status(grpc::ServerContext*, google::protobuf::Message*,
                                           google::protobuf::Message*)>;

class GreeterServiceImpl final : public pb::Greeter::Service {
 public:
  grpc::Status SayHello(grpc::ServerContext* context, const pb::CSReqHello* request,
                        pb::CSResHello* reply) override {
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    return grpc::Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  GreeterServiceImpl service;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
  std::cout << "wait zhi hout" << std::endl;
}

int main(int argc, char** argv) {
  GreeterServiceImpl service;
  std::map<std::string, RpcFunc> mp;

  // 使用 lambda 绑定成员函数指针
  mp["sayHello"] = [&service](grpc::ServerContext* context, google::protobuf::Message* request,
                              google::protobuf::Message* reply) -> grpc::Status {
    return service.SayHello(context, dynamic_cast<const pb::CSReqHello*>(request),
                            dynamic_cast<pb::CSResHello*>(reply));
  };

  RunServer();
  return 0;
}