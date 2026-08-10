#ifndef CERIUM_PROJECT_PROJECT_HPP_
#define CERIUM_PROJECT_PROJECT_HPP_

#include <string>
#include <unordered_map>
#include <memory>
#include <filesystem>

#include "../document/document.hpp"

#include "../debug/logging/ConsoleLoggerMiddleware.hpp"
#include "../debug/logging/FileLoggerMiddleware.hpp"
#include "../debug/logging/Logger.hpp"
#include "../debug/logging/LoggerConfig.hpp"
#include "../debug/logging/Logging.hpp"


class Project {
private:
    std::string name;
    std::unordered_map<std::filesystem::path, std::unique_ptr<Document>> documents;

    std::unique_ptr<Logger> logger;

public:
    Project(std::string name);

    void open_document(std::filesystem::path path, Text text, std::string language = "txt", bool edit = true);
    void close_document(std::filesystem::path path);
	Document& get_document(std::filesystem::path path);
    void save_document(std::filesystem::path path);
    void save_document_as(std::filesystem::path old_path, std::filesystem::path new_path);

    void setupLogger();
};

#endif //CERIUM_PROJECT_PROJECT_HPP_
