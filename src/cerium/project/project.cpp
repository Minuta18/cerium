#include "project.hpp"
#include "../document/text.hpp"

#include <stdexcept>
#include <filesystem>
#include <fstream>

Project::Project(std::string name): name(name){
	
}

void Project::open_document(std::filesystem::path path, Text text, std::string language, bool edit) {
	documents.insert({ path, std::unique_ptr<Document>(new Document(path, text, language, edit)) });

}

void Project::close_document(std::filesystem::path path) {
	documents.erase(path);
}
	
Document& Project::get_document(std::filesystem::path path) {
	auto it = documents.find(path);
	if (it != documents.end()) {
		return *(it->second);
	}
	throw std::runtime_error("Invalid document path");
}

void Project::save_document(std::filesystem::path path) {
	std::ofstream doc(path);

}

bool Project::save_document_as(std::filesystem::path old_path, std::filesystem::path new_path) {
	new_path = ""; // TBD implementation
	old_path = "";
	return false;
}