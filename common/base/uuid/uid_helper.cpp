#include "uid_helper.h"

#include "common/base/uuid/uuid_v4.h"

namespace PROJ_NS {
uint64_t GetUid() {
  UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
  uint64_t uid = uuidGenerator.getUUID().hash();
  return uid & UID_ZONE_MASKBITS;
}

uint64_t GetRuidFromUid(uint64_t uid, uint32_t zone_id) {
  uint64_t ruid = uid;
  ruid |= (static_cast<uint64_t>(zone_id) << UID_ZONE_OFFSETBIT);
  return ruid;
}

uint64_t GetUidFromRuid(uint64_t ruid) { return ruid & UID_ZONE_MASKBITS; }
}  // namespace PROJ_NS