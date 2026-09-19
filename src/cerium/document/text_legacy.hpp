#ifndef CERIUM_DOCUMENT_TEXT_LEGACY_HPP_
#define CERIUM_DOCUMENT_TEXT_LEGACY_HPP_

#include "line.hpp"

#include <vector>
#include <string>
#include <memory>

#include "../debug/logging/ConsoleLoggerMiddleware.hpp"
#include "../debug/logging/FileLoggerMiddleware.hpp"
#include "../debug/logging/Logger.hpp"
#include "../debug/logging/LoggerConfig.hpp"
#include "../debug/logging/Logging.hpp"

class TextLegacy {
private:
    std::vector<Line> text;
    int position;
    int currentColumn;
    int currentLine;
    std::unique_ptr<Logger> logger;
public:
    TextLegacy(std::string content);
    TextLegacy(std::vector<Line> content);

    TextLegacy(const TextLegacy& other);
    TextLegacy& operator=(const TextLegacy& other);

    TextLegacy(TextLegacy&& other) noexcept = default;
    TextLegacy& operator=(TextLegacy&& other) noexcept = default;

    int getPosition();
    int characterCount();

    void allCountBefore();

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

    std::vector<Line> getText();
    std::string getLine(int line);

    void clear();
};

#endif // CERIUM_DOCUMENT_TEXT_LEGACY_HPP_