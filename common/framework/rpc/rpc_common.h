#pragma once

#include <google/protobuf/message.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>

#include <functional>
namespace PROJ_NS {
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define CONCAT_RPC_NAME(class_name, method_name) TOSTRING(class_name) "." TOSTRING(method_name)
#define CONCATENATE_DETAIL(x, y) x##y
#define CONCATENATE(x, y) CONCATENATE_DETAIL(x, y)
#define UNIQUE_NAME(base) CONCATENATE(base, __LINE__)

#define RPC_RET_TYPE ::grpc::Status

using RpcFunc = std::function<grpc::Status(grpc::ServerContext*, google::protobuf::Message*,
                                           google::protobuf::Message*)>;
using MessageFactory = std::function<std::unique_ptr<google::protobuf::Message>()>;

std::map<std::string, RpcFunc>& get_rpc_map();

std::map<std::string, std::pair<MessageFactory, MessageFactory>>& get_factory_map();

#define DECLARE_SERVICE_METHOD(class_name, method_name, req_type, res_type, rpc_obj_name)          \
 public:                                                                                           \
  inline static struct UNIQUE_NAME(class_name##FuncRegister) {                                     \
    UNIQUE_NAME(class_name##FuncRegister)() {                                                        \
      get_rpc_map()[CONCAT_RPC_NAME(class_name, method_name)] =                                    \
          [](grpc::ServerContext* context, google::protobuf::Message* req,                         \
             google::protobuf::Message* res) -> grpc::Status {                                     \
        return class_name::Instance().method_name(context, dynamic_cast<const pb::req_type*>(req), \
                                                  dynamic_cast<pb::res_type*>(res));               \
      };                                                                                           \
      get_factory_map()[CONCAT_RPC_NAME(class_name, method_name)] = {                              \
          []() -> std::unique_ptr<google::protobuf::Message> {                                     \
            return std::make_unique<pb::req_type>();                                               \
          },                                                                                       \
          []() -> std::unique_ptr<google::protobuf::Message> {                                     \
            return std::make_unique<pb::res_type>();                                               \
          }};                                                                                      \
    }                                                                                              \
  } UNIQUE_NAME(class_name##register_inst_);                                                       \
  virtual RPC_RET_TYPE method_name(grpc::ServerContext* ctx, const pb::req_type* req,              \
                                   pb::res_type* res) override {                                   \
    method_name##RpcObj __rpc_object(ctx, req, res);                                               \
    auto ret = __rpc_object.Run(req, res);                                                         \
    return ret;                                                                                    \
  }                                                                                                \
                                                                                                   \
 private:                                                                                          \
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