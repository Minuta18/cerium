#ifndef CERIUM_PROJECT_APPLICATION_HPP_
#define CERIUM_PROJECT_APPLICATION_HPP_

#include "project.hpp"

#include <memory>
#include <filesystem>

#include "debug/logging/ConsoleLoggerMiddleware.hpp"
#include "debug/logging/FileLoggerMiddleware.hpp"
#include "debug/logging/Logger.hpp"
#include "debug/logging/LoggerConfig.hpp"
    

class Application {
private:
    std::unique_ptr<Project> project;

    std::shared_ptr<ConsoleLoggerMiddleware> consoleLogger;
    std::shared_ptr<FileLoggerMiddleware> fileLogger1;
    std::shared_ptr<FileLoggerMiddleware> fileLogger2;

    LoggerConfig cfg;

    std::unique_ptr<Logger> logger;
public:
    Application();

    void run();
    void quit();

    ~Application();
};

#endif //CERIUM_PROJECT_APPLICATION_HPP_
