#include "ConsoleLoggerMiddleware.hpp"
#include <iostream>

void ConsoleLoggerMiddleware::log(const Log& log) {
    if (log.level == LogLevel::Error || log.level == LogLevel::Fatal)
        std::cerr << formatLog(log) << '\n' << std::flush;
    else
        std::cout << formatLog(log) << '\n';
}
