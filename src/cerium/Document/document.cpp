#include "document.hpp"

Document::Document(Document&&, std::string path, std::string language, bool edit) noexcept: path(std::move(path)), language(std::move(language)), edit(std::move(edit))) {

}