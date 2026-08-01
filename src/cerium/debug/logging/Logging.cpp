#include "Logging.hpp"

namespace Logging {

static LoggerConfig defaultConfig;

void setDefaultConfig(LoggerConfig cfg) {
    defaultConfig = std::move(cfg);
}

Logger createLogger(std::string loggerName) {
    return Logger(std::move(loggerName), defaultConfig);
}

} // namespace Logging
