#pragma once

#include "protocol/proto_gen/server/cs_hello.pb.h"
#include "protocol/proto_gen/server/cs_hello.grpc.pb.h"
#include "common/framework/rpc_common.h"

namespace PROJ_NS {
class GreeterServiceImpl final : public pb::Greeter::Service {
  DECLARE_SERVICE_METHOD(SayHello, CSReqHello, CSResHello);
  DECLARE_SERVICE_METHOD(SendChat, CSReqSendChat, CSResSendChat);
};
}