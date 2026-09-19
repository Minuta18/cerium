#include "document.hpp"

Document::Document(Document&& other) noexcept :
	path(std::move(other.path)),
	language(std::move(other.language)),
	text(std::move(other.text)),
	isEditable(other.isEditable) {}

Document::Document(std::filesystem::path path, Text text, std::string language, bool isEditable) : path(path), language(language), isEditable(isEditable), text(text) {}

Document& Document::operator=(Document&& other) noexcept {
    if (this != &other) {
        path = std::move(other.path);
        language = std::move(other.language);
        text = std::move(other.text);
        isEditable = other.isEditable;
    }
    return *this;
}
