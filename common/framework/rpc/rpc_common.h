#pragma once

namespace PROJ_NS {
#define RPC_RET_TYPE ::grpc::Status

#define DECLARE_SERVICE_METHOD(method_name, req_type, res_type, rpc_obj_name)         \
  virtual RPC_RET_TYPE method_name(grpc::ServerContext* ctx, const pb::req_type* req, \
                                   pb::res_type* res) override {                      \
    method_name##RpcObj __rpc_object(ctx, req, res);                                  \
    auto ret = __rpc_object.Run(req, res);                                            \
    return ret;                                                                       \
  }                                                                                   \
  DECLARE_GRPC_OBJECT(method_name, req_type, res_type, rpc_obj_name)

#define DECLARE_GRPC_OBJECT(method_name, req_type, res_type, rpc_obj_name)         \
  DECLARE_GRPC_OBJ_WITH_MEMBER_FUNC(method_name, req_type, res_type, rpc_obj_name) \
  }

#define DECLARE_GRPC_OBJ_WITH_MEMBER_FUNC(method_name, req_type, res_type, base_rpc_obj)      \
  class method_name##RpcObj : public base_rpc_obj {                                           \
   public:                                                                                    \
    method_name##RpcObj(grpc::ServerContext* ctx, const pb::req_type* req, pb::res_type* res) \
        : base_rpc_obj(ctx), request_(*req), response_(*res) {}                               \
    virtual ~method_name##RpcObj() {}                                                         \
    int method_name();                                                                        \
    virtual int ProcessRpc() override final {                                                 \
      int ret = method_name();                                                                \
      return ret;                                                                             \
    }                                                                                         \
                                                                                              \
   private:                                                                                   \
    const pb::req_type& request_;                                                             \
    pb::res_type& response_;

#define IMPLEMENT_SERVICE_METHOD(class_name, method_name) \
  int class_name::method_name##RpcObj::method_name()
}  // namespace PROJ_NS