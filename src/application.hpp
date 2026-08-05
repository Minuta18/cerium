#ifndef CERIUM_PROJECT_APPLICATION_HPP_
#define CERIUM_PROJECT_APPLICATION_HPP_

#include "cerium/project/project.hpp"

#include <memory>
#include <filesystem>

#include "cerium/debug/logging/ConsoleLoggerMiddleware.hpp"
#include "cerium/debug/logging/FileLoggerMiddleware.hpp"
#include "cerium/debug/logging/Logger.hpp"
#include "cerium/debug/logging/LoggerConfig.hpp"
#include "cerium/debug/logging/Logging.hpp"


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
