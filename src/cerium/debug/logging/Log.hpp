#ifndef CERIUM_DEBUG_LOGGING_LOG_HPP_
#define CERIUM_DEBUG_LOGGING_LOG_HPP_

#include "LogLevel.hpp"
#include <string>

struct Log {
  std::string name;
  std::string time;
  LogLevel level;
  std::string message;
};

#endif // CERIUM_DEBUG_LOGGING_LOG_HPP_
