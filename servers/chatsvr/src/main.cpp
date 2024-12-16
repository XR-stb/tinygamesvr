// #include <cstdio>

// int main(int argc, char** argv) {
//   printf("hello chatsvr\n");
//   // printf("GameServer: %lu\n", sizeof(PROJ_NS::GameServer));
//   // return PROJ_NS::ServerBase::RunServer<PROJ_NS::GameServer>(argc, argv);
// }

#include "common/framework/server/server_base.h"
#include "ss_chat_service_impl.h"

int main() {
  std::set<::grpc::Service*> services;
  PROJ_NS::ChatServiceImpl service;
  services.insert(&service);
  PROJ_NS::RunServer(50052, services, "chatsvr");
  return 0;
}