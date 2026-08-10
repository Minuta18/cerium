#include "project.hpp"
#include "../document/text.hpp"

#include <iostream>
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
	if (!doc) {
		std::cout << "document not found";
	}
	Document& document = get_document(path);
	std::vector<Line> documentText = document.text.getText();
	for (size_t i = 0; i < documentText.size(); ++i) {
		doc << documentText[i].content << '\n';
	}
}

bool Project::save_document_as(std::filesystem::path old_path, std::filesystem::path new_path) {
	Document& document = get_document(old_path);
	std::vector<Line> documentText = document.text.getText();
	std::ofstream doc(new_path);
	if (!doc) {
		std::cerr << "Invalid path";
		return false;
	}
	document.path = new_path;
	auto extractedPath = documents.extract(old_path);
	if (extractedPath.empty()) {
		std::cerr << "why would this happen anyways";
		return false;
	}
	extractedPath.key() = new_path;
	documents.insert(std::move(extractedPath));
	save_document(new_path);
	return true;
}