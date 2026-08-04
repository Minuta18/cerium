#ifndef CERIUM_PROJECT_APPLICATION_HPP_
#define CERIUM_PROJECT_APPLICATION_HPP_

#include "project.hpp"

#include <memory>
#include <filesystem>

#include "debug/logging/ConsoleLoggerMiddleware.hpp"
#include "debug/logging/FileLoggerMiddleware.hpp"
#include "debug/logging/Logger.hpp"
#include "debug/logging/LoggerConfig.hpp"
#include "debug/logging/Logging.hpp"


class Application {
private:
    std::unique_ptr<Project> project;

    std::unique_ptr<Logger> logger;
public:
    Application();

    void run();
    void setupLogger();
    void quit();

    ~Application();
};

#endif //CERIUM_PROJECT_APPLICATION_HPP_
