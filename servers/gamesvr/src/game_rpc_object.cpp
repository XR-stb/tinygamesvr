#include <grpcpp/server_context.h>

#include "game_rpc_object.h"

namespace PROJ_NS {
int GameRpcObject::BindData() {
  // TODO: player_ = getPlayerByUid(when login) or getPlayerByRuid
  if (player_) {
    ruid_ = player_->GetRuid();
    // TODO: check is in login or unlogin
  }
  return 0;
}
}  // namespace PROJ_NS
