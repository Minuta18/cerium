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
	bool open = false;
	Document();
public:

};

#endif //CERIUM_DOCUMENT_DOCUMENT_HPP_
