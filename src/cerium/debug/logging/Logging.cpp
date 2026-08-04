#include "Logging.hpp"

namespace Logging {

static LoggerConfig defaultConfig;

void setDefaultConfig(const LoggerConfig& cfg) {
    defaultConfig = cfg;
}

Logger createLogger(std::string loggerName) {
    return Logger(std::move(loggerName), defaultConfig);
}

} // namespace Logging
