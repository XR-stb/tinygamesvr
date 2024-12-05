#pragma once


namespace PROJ_NS {
#define DECLARE_SERVICE_METHOD(method_name, req_type, res_type) \
    grpc::Status method_name(grpc::ServerContext* context, const pb::req_type* req, pb::res_type* res) override;

#define IMPLEMENT_SERVICE_METHOD(class_name, method_name, req_type, res_type) \
    grpc::Status class_name::method_name(grpc::ServerContext* context, const pb::req_type* req, pb::res_type* res)
}