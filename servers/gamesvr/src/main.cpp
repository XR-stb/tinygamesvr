#include "common/framework/server/server_base.h"
#include "framework/rpc/rpc_service_registry.h"

using namespace PROJ_NS;

int main(int argc, char** argv) {
  std::set<::grpc::Service*> services;
  RunServer(50051, GetServiceRegistry(), "gamesvr");
  return 0;
}