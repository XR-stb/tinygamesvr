#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include "common/log/log.h"
#include "common/mongo/mongo.h"
namespace PROJ_NS {
TEST(MongoDBTest, ConnectTest) {
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

  // 删除 恢复原状
  collection.delete_one(document.view());
}
}  // namespace PROJ_NS