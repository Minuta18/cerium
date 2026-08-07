#include "project.hpp"

#include <stdexcept>

Project::Project(std::string name): name(name){
	
}

void Project::open_document(std::string path, std::string language, bool edit) {
	documents.insert({ path, std::make_unique<Document>(Document(std::move(*documents[path]), path, language, edit)) });

}

void Project::close_document(std::string path) {
	documents.erase(path);
}

Document& Project::get_document(std::string path) {
	if documents.count(path) {
		return *documents.at(path);
	}
	else {
		throw std::runtime_error("Invalid document path");
	}
}

void Project::save_document() {

}

bool Project::save_document_as(std::string path) {

}