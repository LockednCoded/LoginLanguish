#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <rapidjson/document.h>
#include "game_manager.h"

#include "stages/credentials_stage.h"

namespace {
    class CredentialsStageTest : public ::testing::Test {
        protected:
            GameManager *gm;
            CredentialsStage *stage;

            CredentialsStageTest() {}

            virtual ~CredentialsStageTest() {}

            // set up a test environment before each test case
            virtual void SetUp() override {
                gm = new GameManager();
                stage = dynamic_cast<CredentialsStage*>(gm->getStage("credentials"));

                // set first name in name stage
                gm->updateField("name", "firstName", "Peter");
                // set last name in name stage
                gm->updateField("name", "lastName", "Lee");
            }

            // tear down a test environment after each test case
            virtual void TearDown() override {
                delete stage;
                delete gm;
            }
    };
}

TEST_F(CredentialsStageTest, SetUsername) {
    gm->updateField("credentials", "username", "peterlee");
    std::string expected = "peterlee";
    rapidjson::Document document;
    std::string result = stage->getFieldStates(document.GetAllocator())["username"]["value"].GetString();
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, SetPassword) {
    gm->updateField("credentials", "password", "password");
    std::string expected = "password";
    rapidjson::Document document;
    std::string result = stage->getFieldStates(document.GetAllocator())["password"]["value"].GetString();
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, EmptyPW){
    gm->updateField("credentials", "password", "");
    std::vector<std::string> expected;
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, TooShortPW){
    gm->updateField("credentials", "password", "pass");
    std::vector<std::string> expected = {stage->tooShortError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoDigitPW){
    gm->updateField("credentials", "password", "password");
    std::vector<std::string> expected = {stage->missingDigitError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoUppercasePW){
    gm->updateField("credentials", "password", "password123");
    std::vector<std::string> expected = {stage->missingUppercaseError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoLowercasePW){
    gm->updateField("credentials", "password", "PASSWORD123");
    std::vector<std::string> expected = {stage->missingLowercaseError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoSpecialCharPW){
    gm->updateField("credentials", "password", "Password123");
    std::vector<std::string> expected = {stage->missingSpecialError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoPrimePW){
    gm->updateField("credentials", "password", "Password-123");
    std::vector<std::string> expected = {stage->missingPrimeError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoInitialsPW){
    gm->updateField("credentials", "password", "PassV-23");
    std::vector<std::string> expected = {stage->missingInitialsError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoColourPW){
    gm->updateField("credentials", "password", "Plate-23");
    std::vector<std::string> expected = {stage->missingColourError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoRomanNumPW){
    gm->updateField("credentials", "password", "mossPlate-23");
    std::vector<std::string> expected = {stage->missingRomanNumError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NonPalindromePW){
    gm->updateField("credentials", "password", "Mossplate-23");
    std::vector<std::string> expected = {stage->notPalindromeError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, TooLongPW){
    gm->updateField("credentials", "password", "thepluMjeffbezos-2-sozebffejMulpeht");
    std::vector<std::string> expected = {stage->tooLongError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, ValidPW){
    gm->updateField("credentials", "password", "pluM-2-Mulp");
    std::vector<std::string> expected;
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_TRUE(result == expected);
}



int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}