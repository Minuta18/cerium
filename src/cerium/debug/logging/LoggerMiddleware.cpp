#include "LoggerMiddleware.hpp"

#include <format>

std::string LoggerMiddleware::formatLog(const Log& log) {
    return std::format(
        "[{}]\t[{}]\t[{}]\t{}",
        log.time,
        logLevelToString(log.level),
        log.name,
        log.message
    );
}
