#pragma once

// #include <grpcpp/grpcpp.h>
#include <grpcpp/server_context.h>
#include <grpcpp/status.h>

#include "protocol/protoconf/server/cs_hello.pb.h"

using grpc::Status;
using grpc::ServerContext;
// using pb::Greeter;
using pb::HelloRequest;
using pb::HelloReply;

class GreeterServiceImpl final : public Greeter::Service {
  Status SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply) override;

  Status SayHelloAgain(ServerContext* context, const HelloRequest* request,
                       HelloReply* reply) override;
};