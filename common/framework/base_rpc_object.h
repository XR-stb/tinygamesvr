#pragma once

#include <google/protobuf/message.h>
#include <grpcpp/server_context.h>

namespace PROJ_NS {
namespace rpc {
class BaseRpcObject {
 public:
  BaseRpcObject(std::shared_ptr<grpc::ServerContext> ctx) : ctx_(std::move(ctx)) {}
  virtual int BindData();
  virtual int Run(const google::protobuf::Message* request, google::protobuf::Message* response) {
    int ret = BindData();
    if (ret != 0) {
      assert(1);  // TODO: log err
      return ret;
    }
    return 0;
  }

 protected:
  std::shared_ptr<grpc::ServerContext> ctx_;
};
}  // namespace rpc
}  // namespace PROJ_NS