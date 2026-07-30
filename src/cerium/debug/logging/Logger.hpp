#ifndef CERIUM_DEBUG_LOGGING_LOGGER_HPP_
#define CERIUM_DEBUG_LOGGING_LOGGER_HPP_

#include <format>
#include <string>
#include <utility>

#include "Log.hpp"
#include "LoggerConfig.hpp"

class Logger {
    std::string loggerName;
    LoggerConfig cfg;

    Log createLog(LogLevel level, const std::string& message) const;

    template <typename... Args>
    void log(LogLevel level, const std::string& message, Args&&... args);

  public:
    explicit Logger(std::string _loggerName, LoggerConfig _cfg);

    template <typename... Args> void debug(const std::string& message, Args&&... args);

    template <typename... Args> void info(const std::string& message, Args&&... args);

    template <typename... Args> void warn(const std::string& message, Args&&... args);

    template <typename... Args> void error(const std::string& message, Args&&... args);

    template <typename... Args> void fatal(const std::string& message, Args&&... args);
};

template <typename... Args> void Logger::debug(const std::string& message, Args&&... args) {
    log(LogLevel::Debug, message, std::forward<Args>(args)...);
}

template <typename... Args> void Logger::info(const std::string& message, Args&&... args) {
    log(LogLevel::Info, message, std::forward<Args>(args)...);
}

template <typename... Args> void Logger::warn(const std::string& message, Args&&... args) {
    log(LogLevel::Warn, message, std::forward<Args>(args)...);
}

template <typename... Args> void Logger::error(const std::string& message, Args&&... args) {
    log(LogLevel::Error, message, std::forward<Args>(args)...);
}

template <typename... Args> void Logger::fatal(const std::string& message, Args&&... args) {
    log(LogLevel::Fatal, message, std::forward<Args>(args)...);
}

template <typename... Args>
void Logger::log(LogLevel level, const std::string& message, Args&&... args) {
    std::string completedMessage = std::vformat(message, std::make_format_args(args...));
    Log entry = createLog(level, completedMessage);

    for (const auto& middleware : cfg.middlewares) {
        if (!middleware)
            continue;
        middleware->log(entry);
    }
}

#endif // CERIUM_DEBUG_LOGGING_LOGGER_HPP_
