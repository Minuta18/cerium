#ifndef CERIUM_DEBUG_LOGGING_LOGGERFILEPOOL_HPP_
#define CERIUM_DEBUG_LOGGING_LOGGERFILEPOOL_HPP_

#include <filesystem>
#include <fstream>
#include <memory>
#include <unordered_map>

class LoggerFilePool {
    static std::unordered_map<std::filesystem::path, std::shared_ptr<std::ofstream>> files;

public:
    static std::shared_ptr<std::ofstream> getFile(const std::filesystem::path& path);
};

#endif
