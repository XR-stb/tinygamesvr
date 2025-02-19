#pragma once

#include <grpcpp/server_context.h>

#include "common/framework/rpc/base_rpc_object.h"
#include "player.h"
#include "servers/gamesvr/src/player.h"

namespace PROJ_NS {
class GPlayer;
class GameRpcObject : public rpc::BaseRpcObject {
 public:
  GameRpcObject(grpc::ServerContext* ctx) : rpc::BaseRpcObject(ctx) {
    ruid_ = 0;
    player_ = nullptr;
  }

  virtual ~GameRpcObject() {}

  int BindData() override;

  inline GPlayer& GetPlayer() { return *player_; }

 protected:
  GPlayer* player_;
  uint64_t ruid_;
};
}  // namespace PROJ_NS
