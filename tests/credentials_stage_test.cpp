#include <gtest/gtest.h>
#include <string>
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


// NOT WORKING
TEST_F(CredentialsStageTest, EmptyPassword) {
    std::string password = "";
    std::string result = stage->getStageErrors({"password", password});
    EXPECT_TRUE(result.compare(password) == 0);
}
// WORKING
TEST_F(CredentialsStageTest, ShortPassword) {
    std::string password = "Pass";
    std::string result = stage->getStageErrors({"password", password});
    EXPECT_TRUE(result.compare("Password must include 8 or more characters.") == 0);
}
// NOT WORKING
TEST_F(CredentialsStageTest, PasswordWithoutCapital) {
    std::string password = "password";
    std::string result = stage->getStageErrors({"password", password});
    EXPECT_TRUE(result.compare("Password must include atleast one uppercase letter (A-Z).") == 0);
}
// NOT WORKING
TEST_F(CredentialsStageTest, PasswordWithoutDigit) {
    std::string password = "Password";
    std::string result = stage->getStageErrors({"password", password});
    EXPECT_TRUE(result.compare("Password must include atleast one digit (0-9).") == 0);
}
// NOT WORKING
TEST_F(CredentialsStageTest, PasswordWithoutSpecial) {
    std::string password = "Password123";
    std::string result = stage->getStageErrors({"password", password});
    EXPECT_TRUE(result.compare("Password must include atleast one special character.") == 0);
}
// NOT WORKING
TEST_F(CredentialsStageTest, ValidPassword) {
    std::string password = "Password-12";
    std::string result = stage->getStageErrors({"password", password});
    EXPECT_TRUE(result.compare(password) == 0);
}



int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}