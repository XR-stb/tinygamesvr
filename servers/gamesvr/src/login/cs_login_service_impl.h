#pragma once

#include "common/framework/rpc/rpc_common.h"
#include "protocol/proto_gen/server/cs_login.grpc.pb.h"
#include "protocol/proto_gen/server/cs_login.pb.h"
#include "servers/gamesvr/src/game_rpc_object.h"

namespace PROJ_NS {
class LoginServiceImpl final : public pb::LoginService::Service {
  DECLARE_SERVICE_METHOD(Login, CSReqLogin, CSResLogin, GameRpcObject);
};
}  // namespace PROJ_NS