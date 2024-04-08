#pragma once

#include "protocol/protoconf/server/cs_hello.pb.h"
#include "protocol/protoconf/server/cs_hello.grpc.pb.h"

using grpc::Status;
using grpc::ServerContext;

using pb::HelloRequest;
using pb::HelloReply;
using pb::Greeter;

class GreeterServiceImpl final : public pb::Greeter::Service {
  Status SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply) override;

  Status SayHelloAgain(ServerContext* context, const HelloRequest* request,
                       HelloReply* reply) override;
};