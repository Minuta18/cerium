#ifndef DEBUG_LOGGING_LOG_HPP_
#define DEBUG_LOGGING_LOG_HPP_

#include "LogLevel.hpp"
#include <string>

struct Log {
  std::string name;
  std::string time;
  LogLevel level;
  std::string message;
};

#endif // DEBUG_LOGGING_LOG_HPP_
