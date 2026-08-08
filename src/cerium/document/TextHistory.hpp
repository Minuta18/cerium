#ifndef CERIUM_TEXT_TEXTHISTORY_HPP_
#define CERIUM_TEXT_TEXTHISTORY_HPP_

#include "text.hpp"
#include "TextChange.hpp"
#include <vector>

class TextHistory {
    std::vector<TextChange> history;
    size_t current = 0;

    void pushChange(TextChange change);

public:
    bool canUndo() const;
    bool canRedo() const;

    void undo(Text& text);
    void redo(Text& text);

    void pushInsert(size_t line, size_t column, std::string text);
    void pushDelete(size_t line, size_t column, std::string text);
};

#endif // CERIUM_TEXT_TEXTHISTORY_HPP_
