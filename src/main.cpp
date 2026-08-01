#include "cerium/debug/logging/Logging.hpp"
#include "cerium/debug/logging/ConsoleLoggerMiddleware.hpp"
#include "cerium/debug/logging/FileLoggerMiddleware.hpp"

int main() {
    auto console = std::make_shared<ConsoleLoggerMiddleware>();
    auto file = std::make_shared<FileLoggerMiddleware>("log.txt");

    LoggerConfig cfg;
    cfg.middlewares.push_back(console);
    cfg.middlewares.push_back(file);

    Logging::setDefaultConfig(std::move(cfg));

    auto logger = Logging::createLogger("cerium.main");

    logger.info("test");

    return 0;
}
