#ifndef CERIUM_PROJECT_PROJECT_HPP_
#define CERIUM_PROJECT_PROJECT_HPP_

#include <string>
#include <unordered_map>
#include <memory>
#include <filesystem>

#include "../document/document.hpp"

class Project {
private:
    std::string name;
    std::unordered_map<std::filesystem::path, std::unique_ptr<Document>> documents;

public:
    Project(std::string name);

    void open_document(std::filesystem::path path, Text text, std::string language = "txt", bool edit = true);
    void close_document(std::filesystem::path path);
	Document& get_document(std::filesystem::path path);
    void save_document(std::filesystem::path path);
    bool save_document_as(std::filesystem::path old_path, std::filesystem::path new_path);
};

#endif //CERIUM_PROJECT_PROJECT_HPP_
