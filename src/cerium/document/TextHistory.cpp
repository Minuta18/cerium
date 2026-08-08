#include "TextHistory.hpp"
#include "TextChange.hpp"
#include <utility>

bool TextHistory::canUndo() const {
    return current > 0;
}

bool TextHistory::canRedo() const {
    return current < history.size();
}

void TextHistory::undo(Text& text) {
    if (!canUndo())
        return;

    --current;
    const TextChange& change = history[current];

    if (change.type == ChangeType::Insert) {
        text.deleteMultiple(change.text.size(), change.line, change.column);
    } else {
        text.paste(change.text, change.column, change.line);
    }
}

void TextHistory::redo(Text& text) {
    if (!canRedo())
        return;

    const TextChange& change = history[current];
    ++current;

    if (change.type == ChangeType::Insert) {
        text.paste(change.text, change.column, change.line);
    } else {
        text.deleteMultiple(change.text.size(), change.line, change.column);
    }
}

void TextHistory::pushChange(TextChange change) {
    history.erase(history.begin() + current, history.end());
    history.push_back(std::move(change));
    ++current;
}

void TextHistory::pushInsert(size_t line, size_t column, std::string text) {
    pushChange(
        {.type = ChangeType::Insert, .line = line, .column = column, .text = std::move(text)}
    );
}

void TextHistory::pushDelete(size_t line, size_t column, std::string text) {
    pushChange(
        {.type = ChangeType::Delete, .line = line, .column = column, .text = std::move(text)}
    );
}
