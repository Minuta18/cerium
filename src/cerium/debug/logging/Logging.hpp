#ifndef CERIUM_DEBUG_LOGGING_LOGGING_HPP_
#define CERIUM_DEBUG_LOGGING_LOGGING_HPP_

#include "Logger.hpp"
#include "LoggerConfig.hpp"

namespace Logging {

void setDefaultConfig(const LoggerConfig& cfg);

Logger createLogger(std::string loggerName);

} // namespace Logging

#endif // CERIUM_DEBUG_LOGGING_LOGGING_HPP_
