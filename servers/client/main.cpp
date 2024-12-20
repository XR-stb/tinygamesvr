#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#include "protocol/proto_gen/server/cs_hello.grpc.pb.h"
#include "protocol/proto_gen/server/cs_hello.pb.h"

int main(int argc, char** argv) {
  // 创建一个 gRPC 通道
  auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());

  // 创建一个客户端存根
  std::unique_ptr<pb::Greeter::Stub> stub = pb::Greeter::NewStub(channel);

  // 创建一个请求
  pb::CSReqHello request;
  request.set_name("World");

  // 创建一个响应
  pb::CSResHello reply;

  // 创建一个客户端上下文
  grpc::ClientContext context;

  // 调用远程方法
  grpc::Status status = stub->SayHello(&context, request, &reply);

  // 检查调用状态
  if (status.ok()) {
    std::cout << "Greeter received: " << reply.message() << std::endl;
  } else {
    std::cout << "gRPC call failed: " << status.error_message() << std::endl;
  }

  return 0;
}