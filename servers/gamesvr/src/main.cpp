// #include <cstdio>
// #include <string_view>
// #include "servers/gamesvr/src/game_server.h"

// int main(int argc, char** argv) {
//   printf("hello gamesvr\n");
//   // printf("GameServer: %lu\n", sizeof(PROJ_NS::GameServer));
//   // return PROJ_NS::ServerBase::RunServer<PROJ_NS::GameServer>(argc, argv);

//   PROJ_NS::RunServer(50051);
// }

#include "common/framework/server/server_base.h"
#include "servers/gamesvr/src/echo/cs_echo_service_impl.h"

int main() {
  std::set<::grpc::Service*> services;
  PROJ_NS::GreeterServiceImpl service;
  services.insert(&service);
  PROJ_NS::RunServer(50051, services, "gamesvr");
  // PROJ_NS::Logger::Instance().init("logs/gamesvr", "dev", 0, 0);
  return 0;
}