#ifndef DEBUG_LOGGING_CONSOLELOGGERMIDDLEWARE_HPP_
#define DEBUG_LOGGING_CONSOLELOGGERMIDDLEWARE_HPP_

#include "LoggerMiddleware.hpp"

class ConsoleLoggerMiddleware : public LoggerMiddleware {
  void log(const Log& log) override;
};

#endif // !DEBUG_LOGGING_CONSOLELOGGERMIDDLEWARE_HPP_
