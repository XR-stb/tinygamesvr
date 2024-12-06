#include "servers/gamesvr/src/echo/cs_echo_service_impl.h"

#include <grpcpp/create_channel.h>

#include <cpp_redis/cpp_redis>

#include "protocol/proto_gen/server/ss_chat.grpc.pb.h"
#include "protocol/proto_gen/server/ss_chat.pb.h"

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
  client.sync_commit();
  // client.sync_commit(std::chrono::milliseconds(100));

  std::cout << "set 'hello' 42: " << set.get() << std::endl;

  cpp_redis::reply r = decrby.get();
  if (r.is_integer()) std::cout << "After 'hello' decrement by 12: " << r.as_integer() << std::endl;
  std::cout << "get 'hello': " << get.get() << std::endl;
  client.sync_commit();
  client.disconnect();

  auto SendChatMessage = [](const std::string& user_id, const std::string& message) {
    std::unique_ptr<pb::Chat::Stub> stub = pb::Chat::NewStub(
        grpc::CreateChannel("localhost:50052", grpc::InsecureChannelCredentials()));
    pb::SSReqSendChat ss_req;
    pb::SSResSendChat ss_res;
    ss_req.set_user_id(user_id);
    ss_req.set_msg(message);

    grpc::ClientContext context;
    grpc::Status status = stub->SendChat(&context, ss_req, &ss_res);

    if (status.ok()) {
      std::cout << "Message sent successfully!" << std::endl;
    } else {
      std::cerr << "Failed to send message: " << status.error_code() << std::endl;
    }
  };

  SendChatMessage("123", req->msg());

  res->set_ret(pb::SUCCESS);
  return grpc::Status::OK;
}
}  // namespace PROJ_NS