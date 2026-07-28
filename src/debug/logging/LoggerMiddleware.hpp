#ifndef DEBUG_LOGGING_LOGGERMIDDLEWARE_HPP_
#define DEBUG_LOGGING_LOGGERMIDDLEWARE_HPP_

#include "Log.hpp"

class LoggerMiddleware {
public:
  virtual ~LoggerMiddleware() = default;

  virtual void log(const Log& log) = 0;
};

#endif // DEBUG_LOGGING_LOGGERMIDDLEWARE_HPP_
