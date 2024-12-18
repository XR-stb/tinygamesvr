#pragma once

#include <grpcpp/grpcpp.h>

#include <set>

namespace PROJ_NS {
std::set<::grpc::Service*>& GetServiceRegistry();

void RegisterService(::grpc::Service* service);

// #define REG_GRPC_SERVICE(Service)  \
//   static Service service_instance{}; \
//   RegisterService(&service_instance);

#define REG_GRPC_SERVICE(Service)                        \
  namespace {                                            \
  struct Service##Registrar {                            \
    Service##Registrar() {                               \
      static Service service_instance;                   \
      PROJ_NS::RegisterService(&service_instance);       \
    }                                                    \
  };                                                     \
  static Service##Registrar global_##Service##Registrar; \
  }

}  // namespace PROJ_NS