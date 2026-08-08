#ifndef CERIUM_PROJECT_PROJECT_HPP_
#define CERIUM_PROJECT_PROJECT_HPP_

#include <string>
#include <unordered_map>
#include <memory>
#include <filesystem>

#include "../Document/document.hpp"

class Project {
private:
    std::string name;
    std::unordered_map<std::filesystem::path, std::unique_ptr<Document>> documents;

public:
    Project(std::string name);

    void open_document(std::string path, std::string language = "plaintext", bool edit = true);
    void close_document(std::string path);
	Document& get_document(std::string path);
    void save_document();
    bool save_document_as(std::string path);
};

#endif //CERIUM_PROJECT_PROJECT_HPP_
