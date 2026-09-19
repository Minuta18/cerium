#include <gtest/gtest.h>

#include "../../src/cerium/document/rope/Rope.hpp"

using cerium::document::Rope;

TEST(Rope, ConstructFromString) {
    Rope r("Hello");
    EXPECT_EQ(r.length(), 5u);
    EXPECT_EQ(r.toString(), "Hello");
}

TEST(Rope, EmptyRope) {
    Rope r;
    EXPECT_EQ(r.length(), 0u);
    EXPECT_EQ(r.toString(), "");
    EXPECT_THROW(r.charAt(0), std::out_of_range);
}

TEST(Rope, CharAt) {
    Rope r("Hello");
    EXPECT_EQ(r.charAt(0), 'H');
    EXPECT_EQ(r.charAt(4), 'o');
}

TEST(Rope, CharAtOutOfRange) {
    Rope r("Hello");
    EXPECT_THROW(r.charAt(5), std::out_of_range);
}

TEST(Rope, Substring) {
    Rope r("Hello World");
    EXPECT_EQ(r.substring(0, 5), "Hello");
    EXPECT_EQ(r.substring(6, 11), "World");
    EXPECT_EQ(r.substring(0, 11), "Hello World");
    EXPECT_EQ(r.substring(5, 5), "");
}

TEST(Rope, SubstringInvalid) {
    Rope r("Hello");
    EXPECT_THROW(r.substring(3, 2), std::out_of_range);
    EXPECT_THROW(r.substring(0, 6), std::out_of_range);
}

TEST(Rope, MultiLine) {
    Rope r("line1\nline2\nline3");
    EXPECT_EQ(r.length(), 17u);
    EXPECT_EQ(r.toString(), "line1\nline2\nline3");
}

TEST(Rope, Copy) {
    Rope a("Hello");
    Rope b = a;
    EXPECT_EQ(b.toString(), "Hello");
    b.insert(0, "X");
    EXPECT_EQ(b.toString(), "XHello");
    EXPECT_EQ(a.toString(), "Hello");
}

TEST(Rope, InsertAtBeginning) {
    Rope r("World");
    r.insert(0, "Hello ");
    EXPECT_EQ(r.toString(), "Hello World");
    EXPECT_EQ(r.length(), 11u);
}

TEST(Rope, InsertAtEnd) {
    Rope r("Hello");
    r.insert(5, " World");
    EXPECT_EQ(r.toString(), "Hello World");
}

TEST(Rope, InsertInMiddle) {
    Rope r("HelloWorld");
    r.insert(5, " ");
    EXPECT_EQ(r.toString(), "Hello World");
}

TEST(Rope, InsertEmpty) {
    Rope r("Hello");
    r.insert(2, "");
    EXPECT_EQ(r.toString(), "Hello");
}

TEST(Rope, InsertInvalid) {
    Rope r("Hello");
    EXPECT_THROW(r.insert(6, "X"), std::out_of_range);
}

TEST(Rope, EraseBeginning) {
    Rope r("Hello World");
    r.erase(0, 6);
    EXPECT_EQ(r.toString(), "World");
}

TEST(Rope, EraseEnd) {
    Rope r("Hello World");
    r.erase(5, 11);
    EXPECT_EQ(r.toString(), "Hello");
}

TEST(Rope, EraseMiddle) {
    Rope r("Hello World");
    r.erase(5, 6);
    EXPECT_EQ(r.toString(), "HelloWorld");
}

TEST(Rope, EraseAll) {
    Rope r("Hello");
    r.erase(0, 5);
    EXPECT_EQ(r.length(), 0u);
    EXPECT_EQ(r.toString(), "");
}

TEST(Rope, EraseEmptyRange) {
    Rope r("Hello");
    r.erase(2, 2);
    EXPECT_EQ(r.toString(), "Hello");
}

TEST(Rope, EraseInvalid) {
    Rope r("Hello");
    EXPECT_THROW(r.erase(3, 2), std::out_of_range);
    EXPECT_THROW(r.erase(0, 6), std::out_of_range);
}

TEST(Rope, Clear) {
    Rope r("Hello");
    r.clear();
    EXPECT_EQ(r.length(), 0u);
    EXPECT_EQ(r.toString(), "");
}

TEST(Rope, ManyInserts) {
    Rope r("");
    for (int i = 0; i < 100; ++i) {
        r.insert(r.length(), "a");
    }
    EXPECT_EQ(r.length(), 100u);
    EXPECT_EQ(r.toString(), std::string(100, 'a'));
}

TEST(Rope, LargeString) {
    std::string big(5000, 'x');
    Rope r(big);
    EXPECT_EQ(r.length(), 5000u);
    EXPECT_EQ(r.toString(), big);

    r.insert(2500, "YYY");
    EXPECT_EQ(r.length(), 5003u);
    EXPECT_EQ(r.charAt(2500), 'Y');
    EXPECT_EQ(r.charAt(2503), 'x');

    r.erase(2500, 2503);
    EXPECT_EQ(r.toString(), big);
}

TEST(Rope, ManyInsertsBalanced) {
    Rope r("");
    for (int i = 0; i < 10000; ++i) {
        r.insert(r.length(), "a");
    }
    EXPECT_EQ(r.length(), 10000u);
    EXPECT_EQ(r.charAt(0), 'a');
    EXPECT_EQ(r.charAt(9999), 'a');
}