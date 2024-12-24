#include "common/framework/server/server_base.h"
#include "servers/gamesvr/src/login/cs_login_service_impl.h"
using namespace PROJ_NS;

int main(int argc, char** argv) {
  ServerBase::Instance().Run("gamesvr", "50051", "5051");
  return 0;
}