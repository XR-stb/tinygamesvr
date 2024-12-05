#include "servers/gamesvr/src/echo/cs_echo_service_impl.h"

#include <cpp_redis/cpp_redis>

namespace PROJ_NS {
IMPLEMENT_SERVICE_METHOD(GreeterServiceImpl, SayHello, CSReqHello, CSResHello) {
  std::string prefix("Hello");
  res->set_message(prefix + req->name());
  return grpc::Status::OK;
}

IMPLEMENT_SERVICE_METHOD(GreeterServiceImpl, SendChat, CSReqSendChat, CSResSendChat) {
  // TODO: send to chatsvr by print

  cpp_redis::client client;
  client.auth("123456");
  client.connect(
      "127.0.0.1", 6379,
      [](const std::string& host, std::size_t port, cpp_redis::client::connect_state status) {
        if (status == cpp_redis::client::connect_state::dropped) {
          std::cout << "client disconnected from " << host << ":" << port << std::endl;
        }
      });

  //! Set a value
  auto set = client.set("hello", "42");
  auto decrby = client.decrby("hello", 12);
  auto get = client.get("hello");

  // commands are pipelined and only sent when client.commit() is called
  // client.commit();

  // synchronous commit, no timeout
  client.sync_commit();

  // synchronous commit, timeout
  // client.sync_commit(std::chrono::milliseconds(100));

  std::cout << "set 'hello' 42: " << set.get() << std::endl;

  cpp_redis::reply r = decrby.get();
  if (r.is_integer()) std::cout << "After 'hello' decrement by 12: " << r.as_integer() << std::endl;

  std::cout << "get 'hello': " << get.get() << std::endl;

  // 执行所有命令（异步）
  client.sync_commit();

  // 关闭连接
  client.disconnect();

  res->set_ret(pb::SUCCESS);
  return grpc::Status::OK;
}
}  // namespace PROJ_NS