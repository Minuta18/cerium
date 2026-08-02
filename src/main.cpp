#include "cerium/debug/logging/ConsoleLoggerMiddleware.hpp"
#include "cerium/debug/logging/FileLoggerMiddleware.hpp"
#include "cerium/debug/logging/Logger.hpp"
#include "cerium/debug/logging/LoggerConfig.hpp"
#include "cerium/project/application.hpp"

#include <filesystem>
#include <memory>
#include <iostream>

int main() {
    auto consoleLogger = std::make_shared<ConsoleLoggerMiddleware>();

    auto fileLogger1 = std::make_shared<FileLoggerMiddleware>(std::filesystem::path("log.txt"));

    auto fileLogger2 = std::make_shared<FileLoggerMiddleware>(std::filesystem::path("log.txt"));

    LoggerConfig cfg;
    cfg.level = LogLevel::Info;
    cfg.middlewares.push_back(consoleLogger);
    cfg.middlewares.push_back(fileLogger1);
    cfg.middlewares.push_back(fileLogger2);

    Logger logger("cerium.main", std::move(cfg));

    logger.debug("This won't be in the logs.");
    logger.info("Test: {}", 57);
    logger.error("Error");

    try {
        Application app;
        app.run();
    } catch (std::exception& e) {
		logger.error("Fatal exception: {}", e.what());
        std::cerr << "Fatal exception: " << e.what() << std::endl;
    }


    return 0;
}
