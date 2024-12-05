#include "servers/gamesvr/src/echo/cs_echo_service_impl.h"

namespace PROJ_NS {
IMPLEMENT_SERVICE_METHOD(GreeterServiceImpl, SayHello, CSReqHello, CSResHello) {
    std::string prefix("Hello");
    res->set_message(prefix + req->name());
    return grpc::Status::OK;
}

IMPLEMENT_SERVICE_METHOD(GreeterServiceImpl, SendChat, CSReqSendChat, CSResSendChat) {
    // TODO: send to chatsvr by print
    return grpc::Status::OK;
}
}