#ifndef CERIUM_DEBUG_LOGGING_LOGGERCONFIG_HPP_
#define CERIUM_DEBUG_LOGGING_LOGGERCONFIG_HPP_

#include <memory>
#include <vector>

#include "LoggerMiddleware.hpp"

struct LoggerConfig {
    std::vector<std::shared_ptr<LoggerMiddleware>> middlewares;
};

#endif // CERIUM_DEBUG_LOGGING_LOGGERCONFIG_HPP_
