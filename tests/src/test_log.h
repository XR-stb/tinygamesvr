#include <gtest/gtest.h>

#include "common/log/log.h"
namespace PROJ_NS {
TEST(LoggerTest, LogMarcoTest) {
  int val = 4, x = 3;
  MINFO("fmt: {1}, {0}", val, x);
  MDEBUG("fmt: {1}, {0}", val, x);
  MERROR("fmt: {1}, {0}", val, x);
  MWARN("fmt: {1}, {0}", val, x);

  MINFO("empty param");
  MDEBUG("empty param");
  MERROR("empty param");
  MWARN("empty param");
}
}  // namespace PROJ_NS