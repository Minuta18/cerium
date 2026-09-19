#ifndef CERIUM_DOCUMENT_TEXT_HPP_
#define CERIUM_DOCUMENT_TEXT_HPP_

#include "storage/ITextStorage.hpp"

#include <memory>
#include <string>

using cerium::document::ITextStorage;

class Text {
public:
    Text();
    explicit Text(std::string content);
    explicit Text(std::unique_ptr<ITextStorage> storage);

    Text(const Text& other);
    Text& operator=(const Text& other);
    Text(Text&& other) noexcept = default;
    Text& operator=(Text&& other) noexcept = default;
    ~Text() = default;

    int getPosition();
    int characterCount();

    void setLine(int line);
    void setColumn(int column);
    void setPosition(int line, int column);
    void setPosition(int pos);

    void pasteInNewLine(std::string newLine, int line);
    void paste(std::string substr);
    void paste(std::string substr, int column, int line);

    void deleteLine(int line);
    void deleteLine();
    void deleteMultiple(int number);
    void deleteMultiple(int number, int line, int column);
    void remove();
    void remove(int line, int column);

    std::string getLine(int line);

    void clear();

    ITextStorage& storage();
    const ITextStorage& storage() const;

    std::string toString() const;

private:
    std::unique_ptr<ITextStorage> text;
    int position = 0;
    int currentColumn = 0;
    int currentLine = 0;
};

#endif //CERIUM_DOCUMENT_TEXT_HPP_