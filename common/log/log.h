#pragma once

#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <memory>
#include <string>

#include "common/helper/singleton.h"

namespace PROJ_NS {
class Logger : public Singleton<Logger> {
 public:
  void init(const std::string& logDir, const std::string& logFilePrefix, int hour = 0,
            int minute = 0);

  template <typename... Args>
  void info(const std::string& fmt, Args&&... args) {
    logger->info(fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void warn(const std::string& fmt, Args&&... args) {
    logger->warn(fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void error(const std::string& fmt, Args&&... args) {
    logger->error(fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void debug(const std::string& fmt, Args&&... args) {
    logger->debug(fmt, std::forward<Args>(args)...);
  }

 public:
  std::shared_ptr<spdlog::logger> logger;
};
}  // namespace PROJ_NS

#define RELATIVE_PATH(file)                                    \
  ([](const char* path) {                                      \
    const char* relative = strstr(path, "tinygamesvr/");       \
    if (relative) {                                            \
      relative += strlen("tinygamesvr/");                      \
      while (*relative == '.' || *relative == '/') ++relative; \
      return relative;                                         \
    }                                                          \
    return path;                                               \
  }(file))

#include <cstdio>  // Include for snprintf
#include <cstdio>  // 引入 snprintf

#define MLOG(level, fmt, ...)                                                                     \
  do {                                                                                            \
    char log_buffer[1024];                                                                        \
    snprintf(log_buffer, sizeof(log_buffer), "%s:%d|%s| " fmt, RELATIVE_PATH(__FILE__), __LINE__, \
             __FUNCTION__, ##__VA_ARGS__);                                                        \
    PROJ_NS::Logger::Instance().level(std::string(log_buffer));                                   \
  } while (0)

#define MINFO(fmt, ...) MLOG(info, "fmt: %s, %s", ##__VA_ARGS__)
#define MWARN(fmt, ...) MLOG(warn, "fmt: %s, %s", ##__VA_ARGS__)
#define MERROR(fmt, ...) MLOG(error, "fmt: %s, %s", ##__VA_ARGS__)
#define MDEBUG(fmt, ...) MLOG(debug, "fmt: %s, %s", ##__VA_ARGS__)