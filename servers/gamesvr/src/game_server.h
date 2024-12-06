#pragma once

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

#include "servers/gamesvr/src/echo/cs_echo_service_impl.h"

namespace PROJ_NS {
class GameServer {};
}  // namespace PROJ_NS