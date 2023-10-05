#include <gtest/gtest.h>
#include <string>
#include "string_utils.h"


class StringUtilsTest : public ::testing::Test {
    protected:
    
};


// STRING UTIL UNIT TESTS

TEST_F(StringUtilsTest, EmptyString) {
    std::string input = "";
    std::string result = string_utils::toTitleCase(input);
    EXPECT_EQ(result, "");
}

TEST_F(StringUtilsTest, ToTitleCase) {
    EXPECT_EQ(string_utils::toTitleCase(""), ""); // empty string
    EXPECT_EQ(string_utils::toTitleCase("hello"), "Hello"); // single word
    EXPECT_EQ(string_utils::toTitleCase("hello world"), "Hello World"); // multiple words
    EXPECT_EQ(string_utils::toTitleCase("Hello World"), "Hello World"); // already title case
    EXPECT_EQ(string_utils::toTitleCase("HELLO WORLD"), "Hello World"); // full caps
    EXPECT_EQ(string_utils::toTitleCase("HeLLo WOrLd"), "Hello World"); // mixed casing
}