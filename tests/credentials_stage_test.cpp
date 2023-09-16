#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <rapidjson/document.h>

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



TEST_F(CredentialsStageTest, EmptyPW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected;
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, TooShortPW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"pass\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected = {stage->tooShortError};
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoDigitPW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"password\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected = {stage->missingDigitError};
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoUppercasePW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"password123\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected = {stage->missingUppercaseError};
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoLowercasePW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"PASSWORD123\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected = {stage->missingLowercaseError};
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoSpecialCharPW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"Password123\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected = {stage->missingSpecialError};
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoPrimePW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"Password-123\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected = {stage->missingPrimeError};
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoColourPW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"PassV-23\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected = {stage->missingColourError};
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoRomanNumPW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"Purple-23\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected = {stage->missingRomanNumError};
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NonPalindromePW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"GreenV-23\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected = {stage->notPalindromeError};
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, TooLongPW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"GreenV-11-VneerG\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected = {stage->tooLongError};
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, ValidPW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"pInk-2-knIp\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected;
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}



int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}