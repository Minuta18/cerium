#include "project.hpp"
#include "../document/text.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>

Project::Project(std::string name): name(name), logger(std::make_unique<Logger>(Logging::createLogger("cerium.project.project"))) {}

void Project::openDocument(std::filesystem::path path, Text text, std::string language, bool edit) {
	documents.insert({ path, std::unique_ptr<Document>(new Document(path, text, language, edit)) });
	logger->info("Successfully opened document at " + path.string());
}

void Project::closeDocument(std::filesystem::path path) {
	documents.erase(path);
	logger->info("Closed document at " + path.string());
}
	
Document& Project::getDocument(std::filesystem::path path) {
	auto it = documents.find(path);
	if (it != documents.end()) {
		return *(it->second);
	}
	logger->error("Invalid document path");
	throw std::runtime_error("Invalid document path");
}

void Project::saveDocument(std::filesystem::path path) {
	std::ofstream doc(path);
	if (!doc) {
		logger->warn("Invalid document");
		return;
	}
	Document& document = getDocument(path);
	std::vector<Line> documentText = document.text.getText();
	for (size_t i = 0; i < documentText.size(); ++i) {
		doc << documentText[i].content << '\n';
	}
	logger->info("Saved document to " + path.string());
}

void Project::saveDocumentAs(std::filesystem::path old_path, std::filesystem::path new_path) {
	Document& document = getDocument(old_path);
	std::vector<Line> documentText = document.text.getText();
	std::ofstream doc(new_path);
	if (!doc) {
		logger->error("Invalid document path to save to");
		throw std::runtime_error("Invalid document path to save to");
	}
	document.path = new_path;
	auto extractedPath = documents.extract(old_path);
	if (extractedPath.empty()) {
		logger->error("Couldn't change path of document");
		throw std::runtime_error("Couldn't change path of document");
	}
	extractedPath.key() = new_path;
	documents.insert(std::move(extractedPath));
	saveDocument(new_path);
	logger->info("Saved document to " + new_path.string());
}
