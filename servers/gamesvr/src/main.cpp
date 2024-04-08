#include <cstdio>
#include <string_view>
#include "servers/gamesvr/src/game_server.h"


int main(int argc, char** argv) {
  printf("hello gamesvr\n");
  // printf("GameServer: %lu\n", sizeof(PROJ_NS::GameServer));
  // return PROJ_NS::ServerBase::RunServer<PROJ_NS::GameServer>(argc, argv);

  PROJ_NS::RunServer(50051);
}
