#include "cerium/debug/logging/Logging.hpp"
#include "cerium/debug/logging/ConsoleLoggerMiddleware.hpp"
#include "cerium/debug/logging/FileLoggerMiddleware.hpp"
#include "cerium/project/application.hpp"

#include <iostream>

int main() {
    const auto console = std::make_shared<ConsoleLoggerMiddleware>();
    const auto file = std::make_shared<FileLoggerMiddleware>("log.txt");

    LoggerConfig cfg;
    cfg.middlewares.push_back(console);
    cfg.middlewares.push_back(file);

    Logging::setDefaultConfig(cfg);

    auto logger = Logging::createLogger("cerium.main");

    logger.info("test");

    try {
        Application app;
        app.run();
    } catch (std::exception& e) {
		logger.error("Fatal exception: {}", e.what());
        std::cerr << "Fatal exception: " << e.what() << std::endl;
    }


    return 0;
}
