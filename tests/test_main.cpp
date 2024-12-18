#include <gtest/gtest.h>

#include "common/log/log.h"
#include "src/test_log.h"
#include "src/test_mongo.h"
#include "src/test_redis.h"
#include "src/test_uid.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  PROJ_NS::Logger::Instance().init("logs/tests", "dev", 0, 0);
  return RUN_ALL_TESTS();
}