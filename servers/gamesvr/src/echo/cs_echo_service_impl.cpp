#include "servers/gamesvr/src/echo/cs_echo_service_impl.h"

Status GreeterServiceImpl::SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply) {
    std::string prefix("Hello");
    reply->set_message(prefix + request->name());
    return Status::OK;
}

Status GreeterServiceImpl::SayHelloAgain(ServerContext* context, const HelloRequest* request, HelloReply* reply) {
    std::string prefix("Hello again");
    reply->set_message(prefix + request->name());
    return Status::OK;
}