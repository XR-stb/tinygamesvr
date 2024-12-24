#include "rpc_service_registry.h"
#include "framework/rpc/rpc_common.h"

namespace PROJ_NS {
std::set<::grpc::Service*>& GetServiceRegistry() {
  static std::set<::grpc::Service*> services;
  return services;
}

void RegisterService(::grpc::Service* service) { GetServiceRegistry().insert(service); }

std::map<std::string, RpcFunc>& get_rpc_map() {
    static std::map<std::string, RpcFunc> rpc_map; // lazy load avoid in register time, the map not initialized
    return rpc_map;
}

std::map<std::string, std::pair<MessageFactory, MessageFactory>>& get_factory_map() {
    static std::map<std::string, std::pair<MessageFactory, MessageFactory>> factory_map;
    return factory_map;
}

}  // namespace PROJ_NS