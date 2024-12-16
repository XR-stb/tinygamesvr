#include "server_base.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

#include "common/log/log.h"
namespace PROJ_NS {
void RunServer(uint16_t port, std::set<::grpc::Service*> services, std::string svr_name) {
  // 日志最先初始化
  PROJ_NS::Logger::Instance().init("logs/" + svr_name, "dev", 0, 0);

  std::string server_address = "0.0.0.0:" + std::to_string(port);
  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  for (auto&& service : services) {
    builder.RegisterService(service);
  }
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}
}  // namespace PROJ_NS