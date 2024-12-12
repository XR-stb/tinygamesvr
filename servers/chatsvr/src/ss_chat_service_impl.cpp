#include "ss_chat_service_impl.h"

#include <grpcpp/support/status.h>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

namespace PROJ_NS {
IMPLEMENT_SERVICE_METHOD(ChatServiceImpl, SendChat, SSReqSendChat, SSResSendChat) {
  std::cout << "chat svr recive:" << "\n"
            << "msg: " << req->msg() << "\n"
            << "user_id: " << req->user_id() << std::endl;

  // 初始化 MongoDB 驱动
  mongocxx::instance instance{};

  // 创建客户端并连接到 MongoDB
  mongocxx::client client{mongocxx::uri{"mongodb://localhost:27017"}};

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