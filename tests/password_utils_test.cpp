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
TEST_F(PasswordUtilsTest, TestIsPalindrome) {
    // test palindromes
    ASSERT_TRUE(isPalindrome("racecar")); // odd
    ASSERT_TRUE(isPalindrome("poop")); // even
    ASSERT_TRUE(isPalindrome("LEVEL")); // uppercase
    ASSERT_TRUE(isPalindrome("MadaM")); // mixed case (symmetrical)
    ASSERT_TRUE(isPalindrome("pass121ssap")); // numbers
    ASSERT_TRUE(isPalindrome("pass-ssap")); // special char
    // test non-palindromes
    ASSERT_FALSE(isPalindrome("hello world"));
    ASSERT_FALSE(isPalindrome("123456"));
    ASSERT_FALSE(isPalindrome("Racecar")); // title case
}

// test cases for isPrime function
TEST_F(PasswordUtilsTest, TestIsPrime) {
    // test prime numbers
    ASSERT_TRUE(isPrime(2));
    ASSERT_TRUE(isPrime(101));
    ASSERT_TRUE(isPrime(104729)); // 6 digit prime
    // test non-prime numbers
    ASSERT_FALSE(isPrime(1)); // common mistake
    ASSERT_FALSE(isPrime(4));
    ASSERT_FALSE(isPrime(15));
}

// test cases for hasPrime function
TEST_F(PasswordUtilsTest, TestHasPrime) {
    // test strings containing prime numbers
    ASSERT_TRUE(hasPrime("The number 17 is prime.")); // has prime
    ASSERT_TRUE(hasPrime("test2test")); // sandwiched - password scenario
    ASSERT_TRUE(hasPrime("123456789 is not prime, but 13 is.")); // standalone
    // test strings without prime numbers
    ASSERT_FALSE(hasPrime("No numbers here.")); // none
    ASSERT_FALSE(hasPrime("The number 4 is not prime.")); // not prime
    ASSERT_FALSE(hasPrime("The number 1 is often mistaken.")); // common mistake
    ASSERT_FALSE(hasPrime("123456789")); // not standalone
}

// test cases for hasColour function
TEST_F(PasswordUtilsTest, TestHasColour) {
    // test strings containing colors
    ASSERT_TRUE(hasColour("blueberry")); // combined
    ASSERT_TRUE(hasColour("The White House, Washington D.C.")); // title case
    ASSERT_TRUE(hasColour("REDRUM")); // uppercase
    // test strings without colors
    ASSERT_FALSE(hasColour("No colours mentioned here.")); // none
    ASSERT_FALSE(hasColour("gren")); // spelling mistake
    ASSERT_FALSE(hasColour("yel-low")); // interrupted
}