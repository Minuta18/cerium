#ifndef CERIUM_TEXT_TEXTHISTORY_HPP_
#define CERIUM_TEXT_TEXTHISTORY_HPP_

#include "TextChange.hpp"
#include <vector>

class TextHistory {
    std::vector<TextChange> history;
    size_t current = 0;

    void pushChange(TextChange change);

public:
    bool canUndo() const;
    bool canRedo() const;

    void undo();
    void redo();

    void pushInsert(size_t position, std::string text);
    void pushDelete(size_t position, std::string text);
};

#endif // CERIUM_TEXT_TEXTHISTORY_HPP_
