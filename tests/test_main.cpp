#include <gtest/gtest.h>

#include "src/test_mongo.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}