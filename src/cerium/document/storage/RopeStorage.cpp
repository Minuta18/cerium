#include "RopeStorage.hpp"

#include <stdexcept>

namespace cerium::document {

RopeStorage::RopeStorage() = default;

RopeStorage::RopeStorage(std::string_view content) : rope(content) {}

std::size_t RopeStorage::length() const {
    return rope.length();
}

char RopeStorage::charAt(std::size_t pos) const {
    return rope.charAt(pos);
}

std::string RopeStorage::substring(std::size_t begin, std::size_t end) const {
    return rope.substring(begin, end);
}

void RopeStorage::insert(std::size_t pos, std::string_view text) {
    rope.insert(pos, text);
}

void RopeStorage::erase(std::size_t begin, std::size_t end) {
    rope.erase(begin, end);
}

void RopeStorage::clear() {
    rope.clear();
}

std::size_t RopeStorage::lineCount() const {
    return rope.lineCount();
}

std::string RopeStorage::lineAt(std::size_t lineIndex) const {
    return rope.lineAt(lineIndex);
}

std::size_t RopeStorage::lineLength(std::size_t lineIndex) const {
    return rope.lineLength(lineIndex);
}

std::pair<std::size_t, std::size_t>
RopeStorage::posToLineColumn(std::size_t pos) const {
    return rope.posToLineColumn(pos);
}

std::size_t RopeStorage::lineColumnToPos(std::size_t line, std::size_t column) const {
    return rope.lineColumnToPos(line, column);
}

std::string RopeStorage::toString() const {
    return rope.toString();
}

}