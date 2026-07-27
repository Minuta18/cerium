#include "Logger.hpp"

Logger::Logger(const std::string& _loggerName) : loggerName(_loggerName)
{
}

Log Logger::createLog(LogLevel level, const std::string& message) const
{
  return { .name = loggerName,
           .time = "00:00", // TODO get real time
           .level = level,
           .message = message };
}
