#pragma once

#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include "servers/gamesvr/src/echo/cs_echo_service_impl.h"

namespace PROJ_NS {
class GameServer {};

void RunServer(uint16_t port);

}  // namespace PROJ_NS