#include <gtest/gtest.h>
#include <string>
#include "password_validator.h"

TEST(PasswordValidatorTest, ValidPassword) {
    std::string password = "password@";
    EXPECT_TRUE(PasswordValidator::Validate(password));
}

TEST(PasswordValidatorTest, PasswordWithoutSymbol) {
    std::string password = "password";
    EXPECT_FALSE(PasswordValidator::Validate(password));
}

TEST(PasswordValidatorTest, EmptyPassword) {
    std::string password = "";
    EXPECT_FALSE(PasswordValidator::Validate(password));
}