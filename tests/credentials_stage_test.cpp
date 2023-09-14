#include <gtest/gtest.h>
#include <string>
#include "credentials_stage.h"

class CredentialsStageTest : public testing::Test {
protected:
    CredentialsStage stage;

    // set up a test environment before each test case
    void SetUp() override {
    }

    // tear down a test environment after each test case
    void TearDown() override {
    }
};


TEST(CredentialsStageTest, ValidPassword) {
    std::string password = "Password123";
    std::string result = stage.getStageErrors({"password", password});
    EXPECT_TRUE(result.compare("password is: " + password) == 0);
}

TEST(CredentialsStageTest, ShortPassword) {
    std::string password = "Pass12";
    std::string result = stage.getStageErrors({"password", password});
    EXPECT_FALSE(result.compare("Password must include 8 or more characters.") == 0);
}

TEST(CredentialsStageTest, PasswordWithoutCapital) {
    std::string password = "password123";
    std::string result = stage.getStageErrors({"password", password});
    EXPECT_FALSE(result.compare("Password must include atleast one capital letter (A-Z).") == 0);
}

TEST(CredentialsStageTest, PasswordWithoutDigit) {
    std::string password = "Password";
    std::string result = stage.getStageErrors({"password", password});
    EXPECT_FALSE(result.compare("Password must include atleast one digit (0-9).") == 0);
}

TEST(CredentialsStageTest, EmptyPassword) {
    std::string password = "";
    std::string result = stage.getStageErrors({"password", password});
    EXPECT_TRUE(result.compare("") == 0);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}