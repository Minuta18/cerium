#include "TextHistory.hpp"
#include "TextChange.hpp"
#include <utility>

bool TextHistory::canUndo() const {
    return current > 0;
}

bool TextHistory::canRedo() const {
    return current < history.size();
}

void TextHistory::undo() {
    if (!canUndo())
        return;

    --current;
}

void TextHistory::redo() {
    if (!canRedo())
        return;

    ++current;
}

void TextHistory::pushChange(TextChange change) {
    history.erase(history.begin() + current, history.end());
    history.push_back(std::move(change));
    ++current;
}

void TextHistory::pushInsert(size_t position, std::string text) {
    pushChange({.type = ChangeType::Insert, .position = position, .text = std::move(text)});
}

void TextHistory::pushDelete(size_t position, std::string text) {
    pushChange({.type = ChangeType::Delete, .position = position, .text = std::move(text)});
}
