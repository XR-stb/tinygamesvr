#include "common/framework/server/server_base.h"
#include "framework/rpc/rpc_service_registry.h"

using namespace PROJ_NS;

int main(int argc, char** argv) {
  ServerBase::Instance().Run("gamesvr", "50052", "5052");
  return 0;
}