#include "ss_chat_service_impl.h"

#include <grpcpp/support/status.h>
#include <spdlog/spdlog.h>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include "common/log/log.h"
#include "common/mongo/mongo.h"

namespace PROJ_NS {
IMPLEMENT_SERVICE_METHOD(ChatServiceImpl, SendChat, SSReqSendChat, SSResSendChat) {
  int val = 4;
  MINFO("what {}", val);
  std::cout << "chat svr recive:" << "\n"
            << "msg: " << req->msg() << "\n"
            << "user_id: " << req->user_id() << std::endl;

  auto&& client = MongoDB::Instance().GetClient();

  // 选择数据库和集合
  auto db = client["testdb"];
  auto collection = db["testcollection"];

  // 插入文档
  bsoncxx::builder::stream::document document{};
  document << "name" << "Alice" << "age" << 30;
  collection.insert_one(document.view());

  // 查询文档
  auto cursor = collection.find({});
  for (auto&& doc : cursor) {
    std::cout << bsoncxx::to_json(doc) << std::endl;
  }

  return grpc::Status::OK;
}
}  // namespace PROJ_NS