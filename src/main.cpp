#include "cerium/debug/logging/ConsoleLoggerMiddleware.hpp"
#include "cerium/debug/logging/FileLoggerMiddleware.hpp"
#include "cerium/debug/logging/Logger.hpp"
#include "cerium/debug/logging/LoggerConfig.hpp"

#include <filesystem>
#include <memory>

int main()
{
  auto consoleLogger = std::make_shared<ConsoleLoggerMiddleware>();
  auto fileLogger = std::make_shared<FileLoggerMiddleware>(std::filesystem::path("log.txt"));

  LoggerConfig cfg;
  cfg.middlewares.push_back(consoleLogger);
  cfg.middlewares.push_back(fileLogger);

  Logger logger("Renderer", std::move(cfg));

  logger.debug("Test: {}", 57);
  logger.info("Info");
  logger.warn("Warn");
  logger.error("Error");
  logger.fatal("Fatal");

  return 0;
}
