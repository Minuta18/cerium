#include "../../src/cerium/document/TextHistory.hpp"

#include <gtest/gtest.h>

TEST(TextHistory, UndoInsert) {
    Text text("Hello");
    TextHistory history;

    text.paste(" World", 5, 0);
    history.submitInsert(0, 5, " World");

    ASSERT_EQ(text.getLine(0), "Hello World");

    history.undo(text);

    EXPECT_EQ(text.getLine(0), "Hello");
}

TEST(TextHistory, RedoInsert) {
    Text text("Hello");
    TextHistory history;

    text.paste(" World", 5, 0);
    history.submitInsert(0, 5, " World");

    history.undo(text);
    ASSERT_EQ(text.getLine(0), "Hello");

    history.redo(text);

    EXPECT_EQ(text.getLine(0), "Hello World");
}

TEST(TextHistory, TransactionIsUndoneAsOneOperation) {
    Text text("Hello");
    TextHistory history;

    TextHistory::Transaction transaction;

    text.paste(" World", 5, 0);
    transaction.pushInsert(0, 5, " World");

    text.paste("!", 11, 0);
    transaction.pushInsert(0, 11, "!");

    history.submit(transaction);

    ASSERT_EQ(text.getLine(0), "Hello World!");

    history.undo(text);

    EXPECT_EQ(text.getLine(0), "Hello");
}

TEST(TextHistory, TransactionIsRedoneAsOneOperation) {
    Text text("Hello");
    TextHistory history;

    TextHistory::Transaction transaction;

    text.paste(" World", 5, 0);
    transaction.pushInsert(0, 5, " World");

    text.paste("!", 11, 0);
    transaction.pushInsert(0, 11, "!");

    history.submit(transaction);

    history.undo(text);
    ASSERT_EQ(text.getLine(0), "Hello");

    history.redo(text);

    EXPECT_EQ(text.getLine(0), "Hello World!");
}

TEST(TextHistory, CannotUndoInitially) {
    Text text("Hello");
    TextHistory history;

    EXPECT_FALSE(history.canUndo());
    EXPECT_FALSE(history.canRedo());
}

TEST(TextHistory, CannotRedoAfterNewChange) {
    Text text("Hello");
    TextHistory history;

    text.paste(" World", 5, 0);
    history.submitInsert(0, 5, " World");

    history.undo(text);

    ASSERT_TRUE(history.canRedo());

    text.paste("!", 5, 0);
    history.submitInsert(0, 5, "!");

    EXPECT_FALSE(history.canRedo());
}
