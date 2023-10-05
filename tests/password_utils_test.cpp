/*!
    @file password_utils_test.cpp
    @brief the unit tests for the password utilities
    @author Jack Searle
    @copyright 2023 Locked & Coded
*/

#include <gtest/gtest.h>
#include "password_utils.cpp"

class PasswordUtilsTest : public ::testing::Test {
    protected:
        void SetUp() override {}
        void TearDown() override {}
};

// test cases for isPalindrome function
TEST_F(PasswordUtilsTest, TestisPalindrome) {
    // test palindromes
    ASSERT_TRUE(password_utils::isPalindrome("racecar")); // odd
    ASSERT_TRUE(password_utils::isPalindrome("poop")); // even
    ASSERT_TRUE(password_utils::isPalindrome("LEVEL")); // uppercase
    ASSERT_TRUE(password_utils::isPalindrome("MadaM")); // mixed case (symmetrical)
    ASSERT_TRUE(password_utils::isPalindrome("pass121ssap")); // numbers
    ASSERT_TRUE(password_utils::isPalindrome("pass-ssap")); // special char
    // test non-palindromes
    ASSERT_FALSE(password_utils::isPalindrome("hello world"));
    ASSERT_FALSE(password_utils::isPalindrome("123456"));
    ASSERT_FALSE(password_utils::isPalindrome("Racecar")); // title case
}

// test cases for isPrime function
TEST_F(PasswordUtilsTest, TestIsPrime) {
    // test prime numbers
    ASSERT_TRUE(password_utils::isPrime(2));
    ASSERT_TRUE(password_utils::isPrime(101));
    ASSERT_TRUE(password_utils::isPrime(104729)); // 6 digit prime
    // test non-prime numbers
    ASSERT_FALSE(password_utils::isPrime(1)); // common mistake
    ASSERT_FALSE(password_utils::isPrime(4));
    ASSERT_FALSE(password_utils::isPrime(15));
}

// test cases for hasPrime function
TEST_F(PasswordUtilsTest, TestHasPrime) {
    // test strings containing prime numbers
    ASSERT_TRUE(password_utils::hasPrime("The number 17 is prime.")); // has prime
    ASSERT_TRUE(password_utils::hasPrime("test2test")); // sandwiched - password scenario
    ASSERT_TRUE(password_utils::hasPrime("123456789 is not prime, but 13 is.")); // standalone
    // test strings without prime numbers
    ASSERT_FALSE(password_utils::hasPrime("No numbers here.")); // none
    ASSERT_FALSE(password_utils::hasPrime("The number 4 is not prime.")); // not prime
    ASSERT_FALSE(password_utils::hasPrime("The number 1 is often mistaken.")); // common mistake
    ASSERT_FALSE(password_utils::hasPrime("123456789")); // not standalone
}

// test cases for hasColour function
TEST_F(PasswordUtilsTest, TestHasColour) {
    // test strings containing colors
    ASSERT_TRUE(password_utils::hasColour("blueberry")); // combined
    ASSERT_TRUE(password_utils::hasColour("The White House, Washington D.C.")); // title case
    ASSERT_TRUE(password_utils::hasColour("REDRUM")); // uppercase
    // test strings without colors
    ASSERT_FALSE(password_utils::hasColour("No colours mentioned here.")); // none
    ASSERT_FALSE(password_utils::hasColour("gren")); // spelling mistake
    ASSERT_FALSE(password_utils::hasColour("yel-low")); // interrupted
}