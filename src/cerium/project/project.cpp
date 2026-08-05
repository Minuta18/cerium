#include "project.hpp"

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
		// Document not found
	}
}

void Project::save_document() {

}