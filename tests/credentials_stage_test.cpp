#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "stages/credentials_stage.h"

namespace {
    class CredentialsStageTest : public ::testing::Test {
        protected:
            CredentialsStage *stage;

            CredentialsStageTest() {}

            virtual ~CredentialsStageTest() {}

            // set up a test environment before each test case
            virtual void SetUp() override {
                stage = new CredentialsStage();
            }

            // tear down a test environment after each test case
            virtual void TearDown() override {
                delete stage;
            }
    };
}



TEST_F(CredentialsStageTest, EmptyPW) {
    std::string password = "";
    std::vector<std::string> expected;
    std::vector<std::string> result = stage->getStageErrors({"password", password});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, TooShortPW) {
    std::string password = "Pass";
    std::vector<std::string> expected = {stage->tooShortError};
    std::vector<std::string> result = stage->getStageErrors({"password", password});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoDigitPW) {
    std::string password = "Password";
    std::vector<std::string> expected = {stage->missingDigitError};
    std::vector<std::string> result = stage->getStageErrors({"password", password});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoUppercasePW) {
    std::string password = "password123";
    std::vector<std::string> expected = {stage->missingUppercaseError};
    std::vector<std::string> result = stage->getStageErrors({"password", password});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoLowercasePW) {
    std::string password = "PASSWORD123";
    std::vector<std::string> expected = {stage->missingLowercaseError};
    std::vector<std::string> result = stage->getStageErrors({"password", password});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoSpecialPW) {
    std::string password = "Password123";
    std::vector<std::string> expected = {stage->missingSpecialError};
    std::vector<std::string> result = stage->getStageErrors({"password", password});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NonPalindromePW) {
    std::string password = "Password-123";
    std::vector<std::string> expected = {stage->notPalindromeError};
    std::vector<std::string> result = stage->getStageErrors({"password", password});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, TooLongPW) {
    std::string password = "Password-1-drowssaP";
    std::vector<std::string> expected = {stage->tooLongError};
    std::vector<std::string> result = stage->getStageErrors({"password", password});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, ValidPW) {
    std::string password = "Pass1-1ssaP";
    std::vector<std::string> expected;
    std::vector<std::string> result = stage->getStageErrors({"password", password});
    EXPECT_TRUE(result == expected);
}



int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}