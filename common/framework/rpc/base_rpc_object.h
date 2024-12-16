#pragma once

#include <google/protobuf/message.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>

#include "common/log/log.h"
#include "rpc_common.h"

namespace PROJ_NS {
namespace rpc {
class BaseRpcObject {
 public:
  BaseRpcObject() = default;
  BaseRpcObject(grpc::ServerContext* ctx) : ctx_(ctx) {}
  virtual ~BaseRpcObject() {}
  virtual int BindData() { return 0; }  // declare and define inline
  virtual int ProcessRpc() = 0;
  virtual RPC_RET_TYPE Run(const google::protobuf::Message* request,
                           google::protobuf::Message* response) {
    int ret = BindData();
    if (ret != 0) {
      MERROR("bind data failed:{}", ret);
      return grpc::Status(grpc::StatusCode::UNKNOWN, "bind data failed");
    }

    ret = ProcessRpc();
    if (ret != 0) {
      // ctx_->code = ret; but here ctx not code, so not check
    }
    return grpc::Status::OK;
  }

 protected:
  grpc::ServerContext* ctx_;
};
}  // namespace rpc
}  // namespace PROJ_NS