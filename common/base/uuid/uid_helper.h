#pragma once
#include <cstdint>

namespace PROJ_NS {
enum {
  UID_ZONE_OFFSETBIT = 32,
  UID_ZONE_MASKBITS = (1ULL << UID_ZONE_OFFSETBIT) - 1,
};

uint64_t GetUid();
uint64_t GetRuidFromUid(uint64_t uid, uint32_t zone_id);
uint64_t GetUidFromRuid(uint64_t ruid);
}  // namespace PROJ_NS