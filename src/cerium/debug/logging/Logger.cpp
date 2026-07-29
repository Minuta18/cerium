#include "Logger.hpp"
#include "../../time/Clock.hpp"

Logger::Logger(std::string _loggerName, LoggerConfig _cfg)
  : loggerName(std::move(_loggerName))
  , cfg(std::move(_cfg))
{
}

Log Logger::createLog(LogLevel level, const std::string& message) const
{
  return { .name = loggerName,
    .time = Clock::getFormattedCurrentTime(),
    .level = level,
    .message = message };
}
