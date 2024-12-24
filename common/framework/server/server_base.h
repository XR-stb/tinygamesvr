#pragma once

#include <grpcpp/impl/service_type.h>
#include <grpcpp/security/server_credentials.h>

#include <cstdint>
#include <set>
#include <zmq.hpp>

#include "framework/rpc/rpc_common.h"
#include "helper/singleton.h"
#include "protocol/proto_gen/server/rpc.pb.h"
namespace PROJ_NS {
class ServerBase : public Singleton<ServerBase> {
 public:
  void Run(std::string svr_name, std::string grpc_port, std::string zmq_port);

 private:
  std::string handleZmqRequest(const std::string& request_str);

  void runZmqServer(std::string port);

  void runGrpcServer(std::string port, std::set<::grpc::Service*>& services);
};

// void RunServer(uint16_t port, std::set<::grpc::Service*> services, std::string svr_name);
}  // namespace PROJ_NS
