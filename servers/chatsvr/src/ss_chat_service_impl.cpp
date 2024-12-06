#include "ss_chat_service_impl.h"

#include <grpcpp/support/status.h>

namespace PROJ_NS {
IMPLEMENT_SERVICE_METHOD(ChatServiceImpl, SendChat, SSReqSendChat, SSResSendChat) {
  std::cout << "chat svr recive:" << "\n"
            << "msg: " << req->msg() << "\n"
            << "user_id: " << req->user_id() << std::endl;
  return grpc::Status::OK;
}
}  // namespace PROJ_NS