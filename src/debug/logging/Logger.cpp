#include "Logger.hpp"

Logger::Logger(std::string _loggerName, LoggerConfig _cfg)
  : loggerName(std::move(_loggerName))
  , cfg(std::move(_cfg))
{
}

Log Logger::createLog(LogLevel level, const std::string& message) const
{
  return { .name = loggerName,
    .time = "00:00", // TODO get real time
    .level = level,
    .message = message };
}
