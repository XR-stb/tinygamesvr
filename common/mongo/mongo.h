#pragma once

#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/collection-fwd.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include "common/helper/singleton.h"
namespace PROJ_NS {
class MongoDB : public Singleton<MongoDB> {
 public:
  MongoDB() : connected(false) {
    // https://www.mongodb.com/zh-cn/docs/languages/cpp/cpp-driver/current/connect/instance/
    // 必需：初始化 MongoDB 驱动实例
    instance = std::make_unique<mongocxx::instance>();
    connect("mongodb://localhost:27017");
  }

  ~MongoDB() = default;

 public:
  mongocxx::client& GetClient() {
    if (!connected) {
      throw std::runtime_error("MongoDB client is not connected.");
    }
    return *client;
  }

  mongocxx::collection GetTable(std::string collection_name) {
    auto&& client = MongoDB::Instance().GetClient();
    auto db = client["TinyGameSvrDB"];
    auto collection = db[collection_name];
    return collection;
  }

 private:
  void connect(const std::string& uri) {
    if (!connected) {
      client = std::make_unique<mongocxx::client>(mongocxx::uri{uri});
      connected = true;
      std::cout << "Connected to MongoDB at " << uri << std::endl;
    }
  }

  bool connected;
  std::unique_ptr<mongocxx::instance> instance;
  std::unique_ptr<mongocxx::client> client;
};
}  // namespace PROJ_NS