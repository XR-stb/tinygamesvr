#include "rpc_service_registry.h"

namespace PROJ_NS {
std::set<::grpc::Service*>& GetServiceRegistry() {
  static std::set<::grpc::Service*> services;
  return services;
}

void RegisterService(::grpc::Service* service) { GetServiceRegistry().insert(service); }

}  // namespace PROJ_NS