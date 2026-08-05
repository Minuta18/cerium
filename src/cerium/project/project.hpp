#ifndef CERIUM_PROJECT_PROJECT_HPP_
#define CERIUM_PROJECT_PROJECT_HPP_

#include <string>
#include <unordered_map>
#include <memory>

#include "../Document/document.hpp"

class Project {
private:
    std::string name;
    std::unordered_map<std::filesystem::path, std::unique_ptr<Document>> documents;

public:
    Project();

    bool set_name(std::string name);

    void open_document();
    void close_document();
	Document get_document(std::string path);
    void save_document();
    bool save_document_as(std::string path);
};

#endif //CERIUM_PROJECT_PROJECT_HPP_
