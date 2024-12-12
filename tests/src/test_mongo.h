#include <gtest/gtest.h>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

TEST(MongoDBTest, ConnectTest) {
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

  // 删除 恢复原状
  collection.delete_one(document.view());
}
