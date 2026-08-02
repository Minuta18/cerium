#include "application.hpp"


Application::Application() {
    project = std::make_unique<Project>();

	consoleLogger = std::make_shared<
		ConsoleLoggerMiddleware>();
	fileLogger1 = std::make_shared<
		FileLoggerMiddleware>(std::filesystem::path("log.txt"));
	fileLogger2 = std::make_shared<
		FileLoggerMiddleware>(std::filesystem::path("log2.txt"));

	cfg.level = LogLevel::Info;
	cfg.middlewares.push_back(consoleLogger);
	cfg.middlewares.push_back(fileLogger1);
	cfg.middlewares.push_back(fileLogger2);

	logger = std::make_unique<Logger>("cerium.application", std::move(cfg));

	(*logger).info("App initialized successfully");
}

void Application::run() {
	(*logger).info("App started");
}
