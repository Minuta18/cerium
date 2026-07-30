#ifndef CERIUM_DEBUG_LOGGING_FILELOGGERMIDDLEWARE_HPP_
#define CERIUM_DEBUG_LOGGING_FILELOGGERMIDDLEWARE_HPP_

#include "LoggerMiddleware.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

class FileLoggerMiddleware : public LoggerMiddleware {
    std::shared_ptr<std::ofstream> file;

public:
    explicit FileLoggerMiddleware(std::filesystem::path path);

    void log(const Log& log) override;
};

#endif // CERIUM_DEBUG_LOGGING_FILELOGGERMIDDLEWARE_HPP_
