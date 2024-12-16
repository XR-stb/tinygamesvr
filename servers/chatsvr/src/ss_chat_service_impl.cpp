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
IMPLEMENT_SERVICE_METHOD(ChatServiceImpl, SendChat) {
  int val = 4;
  MINFO("what {}", val);
  std::cout << "chat svr recive:" << "\n"
            << "msg: " << request_.msg() << "\n"
            << "user_id: " << request_.user_id() << std::endl;

  auto&& client = MongoDB::Instance().GetClient();

  auto db = client["testdb"];
  auto collection = db["testcollection"];

  bsoncxx::builder::stream::document document{};
  document << "name" << "Alice" << "age" << 30;
  collection.insert_one(document.view());

  auto cursor = collection.find({});
  for (auto&& doc : cursor) {
    std::cout << bsoncxx::to_json(doc) << std::endl;
  }

  return 0;
}
}  // namespace PROJ_NS