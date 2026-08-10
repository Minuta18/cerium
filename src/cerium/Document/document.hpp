#ifndef CERIUM_DOCUMENT_DOCUMENT_HPP_
#define CERIUM_DOCUMENT_DOCUMENT_HPP_

#include <string>
#include "text.hpp"
#include <filesystem>

class Document {
	friend class Project;
private:
	std::filesystem::path path;
	std::string language = "txt";
	Text text;
	bool edit = true;

	Document(Document&& other) noexcept;
	Document(std::filesystem::path path, Text text, std::string language = "txt", bool edit = true);
public:
	Document(const Document&) = delete;

	Document& operator=(const Document&) = delete;
	Document& operator=(Document&& other) noexcept;

	~Document() = default;
};

#endif //CERIUM_DOCUMENT_DOCUMENT_HPP_
