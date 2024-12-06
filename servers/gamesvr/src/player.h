#pragma once

#include <cstdint>
namespace PROJ_NS {
class GPlayer {
 public:
  uint64_t GetRuid() { return ruid_; }

 protected:
  uint64_t ruid_;
};
}  // namespace PROJ_NS
