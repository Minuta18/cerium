#include "text.hpp"

#include "storage/VectorStorage.hpp"

#include <stdexcept>
#include <utility>

Text::Text()
    : text(std::make_unique<cerium::document::VectorStorage>()) {}

Text::Text(std::string content)
    : text(std::make_unique<cerium::document::VectorStorage>(content)) {}

Text::Text(std::unique_ptr<ITextStorage> storage)
    : text(std::move(storage)) {
    if (!text) {
        throw std::invalid_argument("Text: null storage");
    }
}

Text::Text(const Text& other)
    : text(std::make_unique<cerium::document::VectorStorage>(other.toString())),
      position(other.position),
      currentColumn(other.currentColumn),
      currentLine(other.currentLine) {}

Text& Text::operator=(const Text& other) {
    if (this != &other) {
        text = std::make_unique<cerium::document::VectorStorage>(other.toString());
        position = other.position;
        currentColumn = other.currentColumn;
        currentLine = other.currentLine;
    }
    return *this;
}

int Text::getPosition() {
    return static_cast<int>(text->lineColumnToPos(
        static_cast<std::size_t>(currentLine),
        static_cast<std::size_t>(currentColumn)));
}

int Text::characterCount() {
    return static_cast<int>(text->length());
}

void Text::setLine(int line) {
    currentLine = line;
}

void Text::setColumn(int column) {
    currentColumn = column;
}

void Text::setPosition(int line, int column) {
    currentLine = line;
    currentColumn = column;
}

void Text::setPosition(int pos) {
    position = pos;
}

void Text::pasteInNewLine(std::string newLine, int line) {
    std::size_t pos = text->lineColumnToPos(
        static_cast<std::size_t>(line), 0);
    text->insert(pos, "\n" + newLine);
}

void Text::paste(std::string substr) {
    std::size_t pos = text->lineColumnToPos(
        static_cast<std::size_t>(currentLine),
        static_cast<std::size_t>(currentColumn));
    text->insert(pos, substr);
}

void Text::paste(std::string substr, int column, int line) {
    std::size_t pos = text->lineColumnToPos(
        static_cast<std::size_t>(line),
        static_cast<std::size_t>(column));
    text->insert(pos, substr);
}

void Text::deleteLine(int line) {
    std::size_t start = text->lineColumnToPos(
        static_cast<std::size_t>(line), 0);
    std::size_t end = (static_cast<std::size_t>(line) + 1 < text->lineCount())
                          ? text->lineColumnToPos(
                                static_cast<std::size_t>(line) + 1, 0)
                          : text->length();
    text->erase(start, end);
}

void Text::deleteLine() {
    deleteLine(currentLine);
}

void Text::deleteMultiple(int number) {
    std::size_t pos = text->lineColumnToPos(
        static_cast<std::size_t>(currentLine),
        static_cast<std::size_t>(currentColumn));
    text->erase(pos, pos + static_cast<std::size_t>(number));
}

void Text::deleteMultiple(int number, int line, int column) {
    std::size_t pos = text->lineColumnToPos(
        static_cast<std::size_t>(line),
        static_cast<std::size_t>(column));
    text->erase(pos, pos + static_cast<std::size_t>(number));
}

void Text::remove() {
    deleteMultiple(1);
}

void Text::remove(int line, int column) {
    deleteMultiple(1, line, column);
}

std::string Text::getLine(int line) {
    return text->lineAt(static_cast<std::size_t>(line));
}

void Text::clear() {
    text->clear();
    currentColumn = 0;
    currentLine = 0;
    position = 0;
}

ITextStorage& Text::storage() {
    return *text;
}

const ITextStorage& Text::storage() const {
    return *text;
}

std::string Text::toString() const {
    return text->toString();
}