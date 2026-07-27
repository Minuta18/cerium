#ifndef DEBUG_LOGGING_LOGGER_HPP_
#define DEBUG_LOGGING_LOGGER_HPP_

#include <string>
#include <utility>

#include "Log.hpp"

class Logger {
  std::string loggerName;

  Log createLog(LogLevel level, const std::string& message) const;

  template<typename... Args>
  void log(LogLevel level, const std::string& message, Args&&... args);

public:
  explicit Logger(const std::string& _loggerName);

  template<typename... Args>
  void info(const std::string& msg, Args&&... args);
};

template<typename... Args>
void Logger::info(const std::string& msg, Args&&... args)
{
  log(LogLevel::Info, msg, std::forward<Args>(args)...);
}

template<typename... Args>
void Logger::log(LogLevel level, const std::string& message, Args&&... args)
{
  Log entry = createLog(level, message);

  (void)entry;
  (void)sizeof...(args);
}

#endif // DEBUG_LOGGING_LOGGER_HPP_
