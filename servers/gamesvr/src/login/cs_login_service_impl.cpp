#include "servers/gamesvr/src/login/cs_login_service_impl.h"

#include <grpcpp/create_channel.h>
#include <spdlog/spdlog.h>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document-fwd.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <cpp_redis/cpp_redis>
#include <cstdint>
#include <string>

#include "base/uuid/uid_helper.h"
#include "common/framework/rpc/rpc_service_registry.h"
#include "common/log/log.h"
#include "common/mongo/mongo.h"
#include "common/redis/redis.h"
#include "protocol/proto_gen/server/code.pb.h"
#include "time/server_time.h"

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

namespace PROJ_NS {
REG_GRPC_SERVICE(LoginServiceImpl);
IMPLEMENT_SERVICE_METHOD(LoginServiceImpl, Login) {
  // TODO: client xx version check
  auto&& db_player_info = MongoDB::Instance().GetTable("DB_PlayerInfo");

  // TODO: 以MD5存密码
  auto&& player = make_document(kvp("account_name", request_.account_name()),
                                kvp("password", request_.password()));
  auto cursor = db_player_info.find(player.view());
  if (cursor.begin() != cursor.end()) {
    // check pass ok
    MINFO("login success");
  } else {
    auto account_cursor =
        db_player_info.find(make_document(kvp("account_name", request_.account_name())));
    if (account_cursor.begin() != account_cursor.end()) {
      MERROR_RETURN(pb::Code::ERR_ACCOUNT_OR_PASSWORD_INCORRECT, "password error");
    } else {
      // 首次注册玩家: 生成UUID, RUID
      uint32_t zone_id = request_.zone_id();
      uint64_t uid = GetUid();
      uint64_t ruid = GetRuidFromUid(uid, zone_id);

      // 记录入DB
      db_player_info.insert_one(make_document(
          kvp("uid", static_cast<int64_t>(uid)), kvp("ruid", static_cast<int64_t>(ruid)),
          kvp("zone_id", static_cast<int32_t>(zone_id)),
          kvp("account_name", request_.account_name()), kvp("password", request_.password()),
          kvp("ruler_name", request_.ruler_name())));

      response_.set_server_time(time::ServerTime::Instance().GetSvrTimeNow(time::kTimeTypeGame));
      response_.mutable_player_info()->set_uid(uid);
      response_.mutable_player_info()->set_uid(ruid);
      response_.mutable_player_info()->set_zone_id(zone_id);
    }
  }

  return 0;
}

}  // namespace PROJ_NS