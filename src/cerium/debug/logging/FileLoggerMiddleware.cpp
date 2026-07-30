#include "FileLoggerMiddleware.hpp"
#include "LoggerFilePool.hpp"

FileLoggerMiddleware::FileLoggerMiddleware(std::filesystem::path path)
    : file(LoggerFilePool::getFile(path)) {
    if (!file->is_open()) {
        throw std::runtime_error("Failed to open log file");
    }
}

void FileLoggerMiddleware::log(const Log& log) {
    *file << formatLog(log) << '\n';
}
