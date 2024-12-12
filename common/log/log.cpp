#include "log.h"

#include <ctime>  // 包含时间相关的头文件

#include "iostream"

namespace PROJ_NS {
void Logger::init(const std::string& logDir, const std::string& logFilePrefix, int hour,
                  int minute) {
  try {
    // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
    std::string pattern = "%Y-%m-%d %H:%M:%S.%e|%l|%t|%v";

    // 获取当前日期和时间
    std::time_t t = std::time(nullptr);
    char dateTimeStr[100];
    if (std::strftime(dateTimeStr, sizeof(dateTimeStr), "%Y%m%d%H", std::localtime(&t))) {
      // 创建按天分割的文件日志接收器
      std::string logFilePath = logDir + "/" + logFilePrefix + "_" + dateTimeStr +
                                ".log";  // ".log" 需要单独书写，否则会带上内置格式的时间
      std::cout << logFilePath << std::endl;
      auto file_sink =
          std::make_shared<spdlog::sinks::daily_file_format_sink_mt>(logFilePath, hour, minute);
      file_sink->set_level(spdlog::level::debug);
      file_sink->set_pattern(pattern);

      // 创建控制台日志接收器
      auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
      console_sink->set_level(spdlog::level::debug);
      console_sink->set_pattern(pattern);

      // 创建多接收器日志器
      logger = std::make_shared<spdlog::logger>("multi_sink",
                                                spdlog::sinks_init_list{console_sink, file_sink});
      logger->set_level(spdlog::level::debug);
      logger->flush_on(spdlog::level::debug);

      spdlog::register_logger(logger);
    } else {
      std::cerr << "Failed to format date and time for log file name." << std::endl;
    }
  } catch (const spdlog::spdlog_ex& ex) {
    std::cerr << "Log initialization failed: " << ex.what() << std::endl;
  }
}
}  // namespace PROJ_NS