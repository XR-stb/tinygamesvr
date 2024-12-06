#pragma once

#include <grpcpp/impl/service_type.h>
#include <cstdint>
#include <set>
namespace PROJ_NS {
// class ServerBase {
// public:
//     struct Stat {
//         UnitStat cpu_usage;
//         CountStat fps;
//     };
// };

void RunServer(uint16_t port, std::set<::grpc::Service*> services);
}
