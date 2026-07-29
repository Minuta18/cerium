#ifndef CERIUM_DEBUG_LOGGING_LOGGERMIDDLEWARE_HPP_
#define CERIUM_DEBUG_LOGGING_LOGGERMIDDLEWARE_HPP_

#include "Log.hpp"

class LoggerMiddleware {
public:
  virtual ~LoggerMiddleware() = default;

  virtual void log(const Log& log) = 0;
};

#endif // CERIUM_DEBUG_LOGGING_LOGGERMIDDLEWARE_HPP_
