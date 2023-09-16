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
                // set first name
                rapidjson::Document doc;
                doc.Parse("[0, \"firstName\", \"Peter\"]");
                rapidjson::Value &jsonArray = doc.GetArray();
                gm->updateField(jsonArray);
                // set last name
                doc.Parse("[0, \"lastName\", \"Lee\"]");
                jsonArray = doc.GetArray();
                gm->updateField(jsonArray);
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

TEST_F(CredentialsStageTest, NoInitialsPW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"PassV-23\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected = {stage->missingInitialsError};
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoColourPW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"Plate-23\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected = {stage->missingColourError};
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NoRomanNumPW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"mossPlate-23\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected = {stage->missingRomanNumError};
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, NonPalindromePW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"Mossplate-23\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected = {stage->notPalindromeError};
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, TooLongPW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"thepluM-2-Mulpeht\"]");
    rapidjson::Value &jsonArray = doc.GetArray();
    stage->update(jsonArray);
    std::vector<std::string> expected = {stage->tooLongError};
    std::vector<std::string> result = stage->getStageErrors({"password"});
    EXPECT_TRUE(result == expected);
}

TEST_F(CredentialsStageTest, ValidPW){
    rapidjson::Document doc;
    doc.Parse("[0, \"password\", \"pluM-2-Mulp\"]");
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