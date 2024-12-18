#include "servers/gamesvr/src/echo/cs_echo_service_impl.h"

#include <grpcpp/create_channel.h>
#include <spdlog/spdlog.h>

#include <cpp_redis/cpp_redis>

#include "common/framework/rpc/rpc_service_registry.h"
#include "common/log/log.h"
#include "common/redis/redis.h"
#include "protocol/proto_gen/server/ss_chat.grpc.pb.h"
#include "protocol/proto_gen/server/ss_chat.pb.h"
namespace PROJ_NS {
REG_GRPC_SERVICE(GreeterServiceImpl);
IMPLEMENT_SERVICE_METHOD(GreeterServiceImpl, SayHello) {
  std::string prefix("Hello ");
  response_.set_message(prefix + request_.name());
  return 0;
}

IMPLEMENT_SERVICE_METHOD(GreeterServiceImpl, SendChat) {
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
      MERROR("SSReqSendChat failed msg: {}", status.error_message());
      std::cerr << "Failed to send message: " << status.error_code() << "|"
                << status.error_message() << std::endl;
    }
  };

  SendChatMessage("123", request_.msg());

  response_.set_ret(pb::SUCCESS);
  return 0;
}
}  // namespace PROJ_NS