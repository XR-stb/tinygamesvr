#pragma once

#include "common/framework/rpc_common.h"
#include "protocol/proto_gen/server/ss_chat.grpc.pb.h"
#include "protocol/proto_gen/server/ss_chat.pb.h"

namespace PROJ_NS {
class ChatServiceImpl final : public pb::Chat::Service {
  DECLARE_SERVICE_METHOD(SendChat, SSReqSendChat, SSResSendChat);
};
}  // namespace PROJ_NS