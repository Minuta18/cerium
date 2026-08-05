#include "document.hpp"

Document::Document(Document&&, std::string path, std::string language, bool edit) noexcept: path(path), language(language), edit(edit) {

}