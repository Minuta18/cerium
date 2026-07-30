#ifndef CERIUM_DEBUG_LOGGING_CONSOLELOGGERMIDDLEWARE_HPP_
#define CERIUM_DEBUG_LOGGING_CONSOLELOGGERMIDDLEWARE_HPP_

#include "LoggerMiddleware.hpp"

class ConsoleLoggerMiddleware : public LoggerMiddleware {
public:
    explicit ConsoleLoggerMiddleware() = default;

    void log(const Log& log) override;
};

#endif // CERIUM_DEBUG_LOGGING_CONSOLELOGGERMIDDLEWARE_HPP_
