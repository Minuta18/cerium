#include "application.hpp"


Application::Application() {
	project = std::make_unique<Project>();

	setupLogger();

	logger->info("App initialized successfully");
}

void Application::run() {
	logger->info("App started");
}

void Application::quit() {
	logger->info("App quitting");
}

void Application::setupLogger() {
	auto consoleMiddleware = std::make_shared<ConsoleLoggerMiddleware>();
	auto fileMiddleware = std::make_shared<FileLoggerMiddleware>("log.txt");

	LoggerConfig cfg;
	cfg.middlewares.push_back(consoleMiddleware);
	cfg.middlewares.push_back(fileMiddleware);

	Logging::setDefaultConfig(std::move(cfg));

	logger = std::make_unique<Logger>(Logging::createLogger("cerium.application"));
}


Application::~Application() {
	logger->info("App terminated sucessfully");
}
