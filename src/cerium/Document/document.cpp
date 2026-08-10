#include "document.hpp"

Document::Document(Document&& other) noexcept :
	path(std::move(other.path)),
	language(std::move(other.language)),
	edit(other.edit),
	text(std::move(other.text)) {}

Document::Document(std::filesystem::path path, Text text, std::string, bool edit) : path(path), language(language), edit(edit), text(text) {}

Document& Document::operator=(Document&& other) noexcept {
    if (this != &other) {
        path = std::move(other.path);
        language = std::move(other.language);
        text = std::move(other.text);
        edit = other.edit;
    }
    return *this;
}
