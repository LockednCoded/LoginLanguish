#include <gtest/gtest.h>
#include <string>
#include "string_utils.h"


class StringUtilsTest : public ::testing::Test {
    protected:
    
};


// STRING UTIL UNIT TESTS

TEST_F(StringUtilsTest, ToLowerCase) {
    EXPECT_EQ(string_utils::toLowerCase(""), ""); // empty string
    EXPECT_EQ(string_utils::toLowerCase("Hello"), "hello"); // single word title case
    EXPECT_EQ(string_utils::toLowerCase("hello world"), "hello world"); // multiple words title case
    EXPECT_EQ(string_utils::toLowerCase("hello world"), "hello world"); // already lowercase
    EXPECT_EQ(string_utils::toLowerCase("HELLO WORLD"), "hello world"); // full caps
    EXPECT_EQ(string_utils::toLowerCase("HeLLo WOrLd"), "hello world"); // mixed casing
}

TEST_F(StringUtilsTest, ToTitleCase) {
    EXPECT_EQ(string_utils::toTitleCase(""), ""); // empty string
    EXPECT_EQ(string_utils::toTitleCase("hello"), "Hello"); // single word
    EXPECT_EQ(string_utils::toTitleCase("hello world"), "Hello World"); // multiple words
    EXPECT_EQ(string_utils::toTitleCase("Hello World"), "Hello World"); // already title case
    EXPECT_EQ(string_utils::toTitleCase("HELLO WORLD"), "Hello World"); // full caps
    EXPECT_EQ(string_utils::toTitleCase("HeLLo WOrLd"), "Hello World"); // mixed casing
}