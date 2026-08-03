#include <gtest/gtest.h>

#include "../../../src/cerium/debug/logging/LoggerFilePool.hpp"

#include <filesystem>

TEST(LoggerFilePool, SamePathReturnsSameFile) {
    auto file1 = LoggerFilePool::getFile("test.txt");
    auto file2 = LoggerFilePool::getFile("test.txt");

    EXPECT_EQ(file1, file2);
}

TEST(LoggerFilePool, DifferentPathsReturnDifferentFiles) {
    auto file1 = LoggerFilePool::getFile("test1.txt");
    auto file2 = LoggerFilePool::getFile("test2.txt");

    EXPECT_NE(file1, file2);
}

TEST(LoggerFilePool, ReturnedFileIsOpen) {
    auto file = LoggerFilePool::getFile("test.txt");

    ASSERT_NE(file, nullptr);
    EXPECT_TRUE(file->is_open());
}
