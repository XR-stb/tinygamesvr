#pragma once

namespace PROJ_NS {
class ServerBase {
public:
    struct Stat {
        UnitStat cpu_usage;
        CountStat fps;
    };
};
}