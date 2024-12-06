#pragma once

namespace PROJ_NS {
#define DECLARE_SERVICE_METHOD(method_name, req_type, res_type)                   \
  grpc::Status method_name(grpc::ServerContext* context, const pb::req_type* req, \
                           pb::res_type* res) override;

#define IMPLEMENT_SERVICE_METHOD(class_name, method_name, req_type, res_type)                 \
  grpc::Status class_name::method_name(grpc::ServerContext* context, const pb::req_type* req, \
                                       pb::res_type* res)

#define DECLARE_SERVICE_METHOD_V2(method_name, req_type, res_type, rpc_obj_name) \
  virtual int method_name(grpc::ServerContext* context, const pb::req_type* req, \
                          pb::res_type* res) override {                          \
    DECLARE_GRPC_OBJECT(method_name, req_type, res_type, rpc_obj_name)

#define DECLARE_GRPC_OBJECT(method_name, req_type, res_type, rpc_obj_name)     \
  DECLARE_GRPC_OBJECT_WITH_FUNC(method_name, req_type, res_type, rpc_obj_name) \
  }

#define DECLARE_GRPC_OBJECT_WITH_FUNC(method_name, req_type, res_type, rpc_obj_name)

}  // namespace PROJ_NS