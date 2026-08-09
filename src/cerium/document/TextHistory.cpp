#include "TextHistory.hpp"

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
    const Transaction& transaction = history[current];

    for (auto it = transaction.changes.rbegin(); it != transaction.changes.rend(); ++it) {
        const Change& change = *it;

        if (change.type == ChangeType::Insert) {
            text.deleteMultiple(change.text.size(), change.line, change.column);
        } else {
            text.paste(change.text, change.column, change.line);
        }
    }
}

void TextHistory::redo(Text& text) {
    if (!canRedo())
        return;

    const Transaction& transaction = history[current];
    for (const Change& change : transaction.changes) {
        if (change.type == ChangeType::Insert) {
            text.paste(change.text, change.column, change.line);
        } else {
            text.deleteMultiple(change.text.size(), change.line, change.column);
        }
    }

    ++current;
}

void TextHistory::submit(Transaction& transaction) {
    history.erase(history.begin() + current, history.end());
    history.push_back(std::move(transaction));
    ++current;
}

void TextHistory::submitInsert(size_t line, size_t column, std::string text) {
    Transaction transaction;
    transaction.pushInsert(line, column, std::move(text));
    submit(transaction);
}

void TextHistory::submitDelete(size_t line, size_t column, std::string text) {
    Transaction transaction;
    transaction.pushDelete(line, column, std::move(text));
    submit(transaction);
}
