/*!
    @file credentials_stage_test.cpp
    @brief the unit tests for the CredentialsStage class
    @author Jack Searle, Cameron Bruce
    @copyright 2023 Locked & Coded
*/

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
                gm->updateField("name", "firstName", "John");
                // set last name in name stage
                gm->updateField("name", "lastName", "Smith");
            }

            // tear down a test environment after each test case
            virtual void TearDown() override {
                delete stage;
                delete gm;
            }
    };
}


// USERNAME UNIT TESTS

TEST_F(CredentialsStageTest, SetUsername){
    gm->updateField("credentials", "username", "johnsmith");
    std::string expected = "johnsmith";
    rapidjson::Document document;
    std::string result = stage->getFieldStates(document.GetAllocator())["username"]["value"].GetString();
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, TooShortUN){
    gm->updateField("credentials", "username", "john");
    std::vector<std::string> expected = {stage->lengthError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "username");
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, TooLongUN){
    gm->updateField("credentials", "username", "john_smith_likes_long_usernames");
    std::vector<std::string> expected = {stage->lengthError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "username");
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, InvalidCharUN){
    gm->updateField("credentials", "username", "J()HN_SM|TH");
    std::vector<std::string> expected = {stage->invalidCharError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "username");
    EXPECT_EQ(result, expected);
}

// TEST_F(CredentialsStageTest, takenUN){
//     gm->updateField("credentials", "username", "johnsmith");
//     std::vector<std::string> expected = {stage->takenError + "\nConsider JohnStinks420, Xx_John_Smith_Xx."};
//     std::vector<std::string> result = gm->getFieldErrors("credentials", "username");
//     EXPECT_EQ(result, expected);
// }

TEST_F(CredentialsStageTest, validUN){
    gm->updateField("credentials", "username", "JohnStinks420");
    std::vector<std::string> expected;
    std::vector<std::string> result = gm->getFieldErrors("credentials", "username");
    EXPECT_EQ(result, expected);
}


// PASSWORD UNIT TESTS

TEST_F(CredentialsStageTest, SetPassword){
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
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, TooShortPW){
    gm->updateField("credentials", "password", "pass");
    std::vector<std::string> expected = {stage->tooShortError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, NoDigitPW){
    gm->updateField("credentials", "password", "password");
    std::vector<std::string> expected = {stage->missingDigitError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, NoUppercasePW){
    gm->updateField("credentials", "password", "password123");
    std::vector<std::string> expected = {stage->missingUppercaseError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, NoLowercasePW){
    gm->updateField("credentials", "password", "PASSWORD123");
    std::vector<std::string> expected = {stage->missingLowercaseError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, NoSpecialCharPW){
    gm->updateField("credentials", "password", "Password123");
    std::vector<std::string> expected = {stage->missingSpecialError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, NoPrimePW){
    gm->updateField("credentials", "password", "Password-123");
    std::vector<std::string> expected = {stage->missingPrimeError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, NoInitialsPW){
    gm->updateField("credentials", "password", "Password-23");
    std::vector<std::string> expected = {stage->missingInitialsError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, NoColourPW){
    gm->updateField("credentials", "password", "JS-pass-23");
    std::vector<std::string> expected = {stage->missingColourError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, NoRomanNumPW){
    gm->updateField("credentials", "password", "JS-green-23");
    std::vector<std::string> expected = {stage->missingRomanNumError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, NonPalindromePW){
    gm->updateField("credentials", "password", "JS-greenV-23");
    std::vector<std::string> expected = {stage->notPalindromeError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, TooLongPW){
    gm->updateField("credentials", "password", "JS-greenV-101-Vneerg-SJ");
    std::vector<std::string> expected = {stage->tooLongError};
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, ValidPW){
    gm->updateField("credentials", "password", "jskyV-2-Vyksj");
    std::vector<std::string> expected;
    std::vector<std::string> result = gm->getFieldErrors("credentials", "password");
    EXPECT_EQ(result, expected);
}


// VALIDATION UNIT TESTS

TEST_F(CredentialsStageTest, EmptyValidation) {
    bool expected = false;
    bool result = stage->validateStage();
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, UsernameOnlyValidation) {
    gm->updateField("credentials", "username", "JohnStinks420");
    bool expected = false;
    bool result = stage->validateStage();
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, PasswordOnlyValidation) {
    gm->updateField("credentials", "password", "jskyV-2-Vyksj");
    bool expected = false;
    bool result = stage->validateStage();
    EXPECT_EQ(result, expected);
}

TEST_F(CredentialsStageTest, SuccessfulValidation) {
    gm->updateField("credentials", "username", "JohnStinks420");
    gm->updateField("credentials", "password", "jskyV-2-Vyksj");
    bool expected = true;
    bool result = stage->validateStage();
    EXPECT_EQ(result, expected);
}