#include "LoggerFilePool.hpp"
#include <fstream>
#include <memory>

std::unordered_map<std::filesystem::path, std::shared_ptr<std::ofstream>> LoggerFilePool::files{};

std::shared_ptr<std::ofstream> LoggerFilePool::getFile(const std::filesystem::path& path) {
    auto it = files.find(path);

    if (it != files.end()) {
        return it->second;
    }

    auto file = std::make_shared<std::ofstream>(path, std::ios::app);

    if (!file->is_open()) {
        return nullptr;
    }

    files.emplace(path, file);

    return file;
}
