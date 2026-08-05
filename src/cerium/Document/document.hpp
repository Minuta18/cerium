#ifndef CERIUM_DOCUMENT_DOCUMENT_HPP_
#define CERIUM_DOCUMENT_DOCUMENT_HPP_

#include <string>
#include "../project/project.hpp"

class Document {
	friend class Project;
private:
	std::string path;
	std::string language = "plaintext";
	bool edit = true;

	Document(Document&& document, std::string path, std::string language = "plaintext", bool edit = true) noexcept;
public:
	Document(const Document&) = delete;

	Document& operator=(const Document&) = delete;
	Document& operator=(Document&& document) noexcept;

};

#endif //CERIUM_DOCUMENT_DOCUMENT_HPP_
