#include "document.hpp"

Document::Document(std::string path, std::string language, bool edit) noexcept {
	this->path = path;
	this->language = language;
	this->edit = edit;
}