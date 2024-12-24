#pragma once

#include "common/framework/rpc/rpc_common.h"
#include "protocol/proto_gen/server/cs_hello.grpc.pb.h"
#include "protocol/proto_gen/server/cs_hello.pb.h"
#include "servers/gamesvr/src/game_rpc_object.h"

namespace PROJ_NS {
class GreeterServiceImpl final : public pb::Greeter::Service, public Singleton<GreeterServiceImpl> {
  DECLARE_SERVICE_METHOD(GreeterServiceImpl, SayHello, CSReqHello, CSResHello, GameRpcObject);
  DECLARE_SERVICE_METHOD(GreeterServiceImpl, SendChat, CSReqSendChat, CSResSendChat, GameRpcObject);
};
}  // namespace PROJ_NS