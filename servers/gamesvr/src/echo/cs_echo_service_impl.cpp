#include "servers/gamesvr/src/echo/cs_echo_service_impl.h"

#include <grpcpp/create_channel.h>
#include <spdlog/spdlog.h>

#include <cpp_redis/cpp_redis>

#include "common/redis/redis.h"
#include "protocol/proto_gen/server/ss_chat.grpc.pb.h"
#include "protocol/proto_gen/server/ss_chat.pb.h"
namespace PROJ_NS {
IMPLEMENT_SERVICE_METHOD(GreeterServiceImpl, SayHello, CSReqHello, CSResHello) {
  std::string prefix("Hello");
  res->set_message(prefix + req->name());
  return grpc::Status::OK;
}

IMPLEMENT_SERVICE_METHOD(GreeterServiceImpl, SendChat, CSReqSendChat, CSResSendChat) {
  spdlog::info("CSReqSendChat");

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