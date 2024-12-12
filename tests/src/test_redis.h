#include <gtest/gtest.h>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include "common/redis/redis.h"
namespace PROJ_NS {
TEST(RedisTest, ConnectTest) {
  auto&& redis_client = Redis::Instance().GetClient();

  //! Set a value
  auto set = redis_client.set("hello", "42");
  auto decrby = redis_client.decrby("hello", 12);
  auto get = redis_client.get("hello");

  // commands are pipelined and only sent when client.commit() is called
  // client.commit();
  redis_client.sync_commit();
  // client.sync_commit(std::chrono::milliseconds(100));

  std::cout << "set 'hello' 42: " << set.get() << std::endl;

  cpp_redis::reply r = decrby.get();
  if (r.is_integer()) std::cout << "After 'hello' decrement by 12: " << r.as_integer() << std::endl;
  std::cout << "get 'hello': " << get.get() << std::endl;
  EXPECT_EQ(r.as_integer(), 30);
}
}  // namespace PROJ_NS