#pragma once

#include <common/marco/marco.h>
#include <limits>

namespace PROJ_NS {
class CountStat {
    uint32_t max_value_per_second = std::numeric_limits<uint32_t>::max();
    uint32_t min_value_per_second = std::numeric_limits<uint32_t>::min();
};
}  // namespace PROJ_NS