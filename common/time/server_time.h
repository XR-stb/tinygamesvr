#pragma once

#include <sys/time.h>

#include "helper/singleton.h"

namespace PROJ_NS {
namespace time {
struct TimeOffsetCtx {
  int offset;  // 时间偏移量
};

enum TimeType { kTimeTypeGame = 0, kTimeTypeNature = 1 };

class ServerTime : public Singleton<ServerTime> {
 public:
  ServerTime() = default;
  ~ServerTime() = default;

 public:
  inline void Update() { ::gettimeofday(&now_tv_, nullptr); }

  inline int GetSvrTimeNow(TimeType type, bool force = false) {
    if (type == kTimeTypeGame) {
      return GetOffset() + GetSvrTimeNow(kTimeTypeNature);
    }
    if (force) {
      Update();
    }
    return now_tv_.tv_sec;
  }

  inline int GetOffset() const { return offset_ctx != nullptr ? offset_ctx->offset : 0; }

 private:
  TimeOffsetCtx* offset_ctx =
      nullptr;  // The pointer is used to point to the memory allocated by mmap
  timeval now_tv_;
};
}  // namespace time
}  // namespace PROJ_NS