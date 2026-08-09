#ifndef CERIUM_DOCUMENT_TEXTHISTORY_HPP_
#define CERIUM_DOCUMENT_TEXTHISTORY_HPP_

#include "text.hpp"

#include <vector>
#include <cstddef>
#include <string>

class TextHistory {
public:
    enum class ChangeType { Insert, Delete };
    struct Change {
        ChangeType type;

        size_t line;
        size_t column;

        std::string text;
    };

    struct Transaction {
        void pushInsert(size_t line, size_t column, std::string text) {
            changes.push_back(
                {.type = ChangeType::Insert,
                 .line = line,
                 .column = column,
                 .text = std::move(text)}
            );
        }
        void pushDelete(size_t line, size_t column, std::string text) {
            changes.push_back(
                {.type = ChangeType::Delete,
                 .line = line,
                 .column = column,
                 .text = std::move(text)}
            );
        }
        std::vector<Change> changes;
    };
    bool canUndo() const;
    bool canRedo() const;

    void undo(Text& text);
    void redo(Text& text);

    void submit(Transaction& transaction);
    void submitInsert(size_t line, size_t column, std::string text);
    void submitDelete(size_t line, size_t column, std::string text);

private:
    std::vector<Transaction> history;
    size_t current = 0;
};

#endif // CERIUM_DOCUMENT_TEXTHISTORY_HPP_
