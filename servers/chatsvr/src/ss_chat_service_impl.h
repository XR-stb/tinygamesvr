#pragma once

#include "common/framework/rpc/rpc_common.h"
#include "framework/rpc/base_rpc_object.h"
#include "protocol/proto_gen/server/ss_chat.grpc.pb.h"
#include "protocol/proto_gen/server/ss_chat.pb.h"

namespace PROJ_NS {
class ChatServiceImpl final : public pb::Chat::Service, public Singleton<ChatServiceImpl> {
  DECLARE_SERVICE_METHOD(ChatServiceImpl, SendChat, SSReqSendChat, SSResSendChat,
                         rpc::BaseRpcObject);
};
}  // namespace PROJ_NS