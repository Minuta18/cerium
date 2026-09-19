#include <gtest/gtest.h>

#include "../../src/cerium/document/storage/RopeStorage.hpp"

using cerium::document::RopeStorage;

TEST(RopeStorage, Length) {
    RopeStorage s("Hello");
    EXPECT_EQ(s.length(), 5u);
    EXPECT_EQ(s.toString(), "Hello");
}

TEST(RopeStorage, EmptyLength) {
    RopeStorage s("");
    EXPECT_EQ(s.length(), 0u);
    EXPECT_EQ(s.lineCount(), 1u);
    EXPECT_EQ(s.lineAt(0), "");
    EXPECT_EQ(s.lineLength(0), 0u);
}

TEST(RopeStorage, SingleLineCount) {
    RopeStorage s("Hello");
    EXPECT_EQ(s.lineCount(), 1u);
    EXPECT_EQ(s.lineAt(0), "Hello");
    EXPECT_EQ(s.lineLength(0), 5u);
}

TEST(RopeStorage, TwoLines) {
    RopeStorage s("Hello\nWorld");
    EXPECT_EQ(s.lineCount(), 2u);
    EXPECT_EQ(s.lineAt(0), "Hello");
    EXPECT_EQ(s.lineAt(1), "World");
    EXPECT_EQ(s.lineLength(0), 5u);
    EXPECT_EQ(s.lineLength(1), 5u);
}

TEST(RopeStorage, TrailingNewline) {
    RopeStorage s("Hello\n");
    EXPECT_EQ(s.lineCount(), 2u);
    EXPECT_EQ(s.lineAt(0), "Hello");
    EXPECT_EQ(s.lineAt(1), "");
}

TEST(RopeStorage, EmptyLines) {
    RopeStorage s("\n\n");
    EXPECT_EQ(s.lineCount(), 3u);
    EXPECT_EQ(s.lineAt(0), "");
    EXPECT_EQ(s.lineAt(1), "");
    EXPECT_EQ(s.lineAt(2), "");
}

TEST(RopeStorage, MultiLine) {
    RopeStorage s("line1\nline2\nline3");
    EXPECT_EQ(s.lineCount(), 3u);
    EXPECT_EQ(s.lineAt(0), "line1");
    EXPECT_EQ(s.lineAt(1), "line2");
    EXPECT_EQ(s.lineAt(2), "line3");
}

TEST(RopeStorage, LineAtOutOfRange) {
    RopeStorage s("Hello");
    EXPECT_THROW(s.lineAt(1), std::out_of_range);
}

TEST(RopeStorage, PosToLineColumn) {
    RopeStorage s("Hello\nWorld");

    EXPECT_EQ(s.posToLineColumn(0), std::make_pair(0u, 0u));
    EXPECT_EQ(s.posToLineColumn(4), std::make_pair(0u, 4u));
    EXPECT_EQ(s.posToLineColumn(6), std::make_pair(1u, 0u));
    EXPECT_EQ(s.posToLineColumn(10), std::make_pair(1u, 4u));
    EXPECT_EQ(s.posToLineColumn(11), std::make_pair(1u, 5u));
}

TEST(RopeStorage, PosToLineColumnMultiLine) {
    RopeStorage s("a\nbb\nccc");

    EXPECT_EQ(s.posToLineColumn(0), std::make_pair(0u, 0u));
    EXPECT_EQ(s.posToLineColumn(2), std::make_pair(1u, 0u));
    EXPECT_EQ(s.posToLineColumn(3), std::make_pair(1u, 1u));
    EXPECT_EQ(s.posToLineColumn(5), std::make_pair(2u, 0u));
    EXPECT_EQ(s.posToLineColumn(8), std::make_pair(2u, 3u));
}

TEST(RopeStorage, PosToLineColumnOutOfRange) {
    RopeStorage s("Hello");
    EXPECT_THROW(s.posToLineColumn(6), std::out_of_range);
}

TEST(RopeStorage, LineColumnToPos) {
    RopeStorage s("Hello\nWorld");

    EXPECT_EQ(s.lineColumnToPos(0, 0), 0u);
    EXPECT_EQ(s.lineColumnToPos(0, 5), 5u);
    EXPECT_EQ(s.lineColumnToPos(1, 0), 6u);
    EXPECT_EQ(s.lineColumnToPos(1, 5), 11u);
}

TEST(RopeStorage, LineColumnToPosMultiLine) {
    RopeStorage s("a\nbb\nccc");

    EXPECT_EQ(s.lineColumnToPos(0, 0), 0u);
    EXPECT_EQ(s.lineColumnToPos(1, 0), 2u);
    EXPECT_EQ(s.lineColumnToPos(2, 0), 5u);
    EXPECT_EQ(s.lineColumnToPos(2, 3), 8u);
}

TEST(RopeStorage, LineColumnToPosInvalid) {
    RopeStorage s("Hello\nWorld");
    EXPECT_THROW(s.lineColumnToPos(2, 0), std::out_of_range);
    EXPECT_THROW(s.lineColumnToPos(0, 6), std::out_of_range);
}

TEST(RopeStorage, RoundTrip) {
    RopeStorage s("abc\ndefg\nhi");

    for (std::size_t pos = 0; pos <= s.length(); ++pos) {
        auto [line, col] = s.posToLineColumn(pos);
        EXPECT_EQ(s.lineColumnToPos(line, col), pos);
    }
}

TEST(RopeStorage, InsertUpdatesLines) {
    RopeStorage s("Hello World");
    s.insert(5, "\n");
    EXPECT_EQ(s.lineCount(), 2u);
    EXPECT_EQ(s.lineAt(0), "Hello");
    EXPECT_EQ(s.lineAt(1), " World");
}

TEST(RopeStorage, EraseMergesLines) {
    RopeStorage s("Hello\nWorld");
    s.erase(5, 6);
    EXPECT_EQ(s.lineCount(), 1u);
    EXPECT_EQ(s.lineAt(0), "HelloWorld");
}