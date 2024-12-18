#include <gtest/gtest.h>

#include "base/uuid/uid_helper.h"
#include "log/log.h"

namespace PROJ_NS {
TEST(UUidTest, UidTest) {
  for (int i = 0; i < 1e4; i++) {
    uint64_t uid = GetUid();
    uint64_t ruid = GetRuidFromUid(uid, 42);
    uint64_t convert_uid = GetUidFromRuid(ruid);
    EXPECT_EQ(uid, convert_uid);
    MDEBUG("uid: {}|ruid: {}", uid, ruid);
  }
}
}  // namespace PROJ_NS