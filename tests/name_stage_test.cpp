/*!
    @file name_stage_test.cpp
    @brief the unit tests for the NameStage class
    @author Cameron Bruce, Jack Searle
    @copyright 2023 Locked & Coded
*/

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <rapidjson/document.h>
#include "game_manager.h"

#include "stages/name_stage.h"

namespace {
    class NameStageTest : public ::testing::Test {
        protected:
            GameManager *gm;
            NameStage *stage;

            NameStageTest() {}

            virtual ~NameStageTest() {}

            // set up a test environment before each test case
            virtual void SetUp() override {
                gm = new GameManager();
                stage = dynamic_cast<NameStage*>(gm->getStage("name"));
            }

            // tear down a test environment after each test case
            virtual void TearDown() override {
                delete stage;
                delete gm;
            }
    };
}


// NAME UNIT TESTS

TEST_F(NameStageTest, SetFirstName) {
    gm->updateField("name", "firstName", "John");
    std::string expected = "John";
    rapidjson::Document document;
    std::string result = stage->getFieldStates(document.GetAllocator())["firstName"]["value"].GetString();
    EXPECT_EQ(result, expected);
}

TEST_F(NameStageTest, SetLastName) {
    gm->updateField("name", "lastName", "Smith");
    std::string expected = "Smith";
    rapidjson::Document document;
    std::string result = stage->getFieldStates(document.GetAllocator())["lastName"]["value"].GetString();
    EXPECT_EQ(result, expected);
}

TEST_F(NameStageTest, TooLongFirstName) {
    gm->updateField("name", "firstName", "Johnathankyouverymuch");
    std::vector<std::string> expected = {stage->fNameLengthError};
    std::vector<std::string> result = gm->getFieldErrors("name", "firstName");
    EXPECT_EQ(result, expected);
}

TEST_F(NameStageTest, TooLongLastName) {
    gm->updateField("name", "lastName", "Smithsonianterramantis");
    std::vector<std::string> expected = {stage->lNameLengthError};
    std::vector<std::string> result = gm->getFieldErrors("name", "lastName");
    EXPECT_EQ(result, expected);
}

TEST_F(NameStageTest, InvalidCharFirstName) {
    gm->updateField("name", "firstName", "J*hn");
    std::vector<std::string> expected = {stage->fNameInvalidCharError};
    std::vector<std::string> result = gm->getFieldErrors("name", "firstName");
    EXPECT_EQ(result, expected);
}

TEST_F(NameStageTest, InvalidCharLastName) {
    gm->updateField("name", "lastName", "Sm!th");
    std::vector<std::string> expected = {stage->lNameInvalidCharError};
    std::vector<std::string> result = gm->getFieldErrors("name", "lastName");
    EXPECT_EQ(result, expected);
}


// VALIDATION UNIT TESTS

TEST_F(NameStageTest, EmptyValidation) {
    bool expected = false;
    bool result = stage->validateStage();
    EXPECT_EQ(result, expected);
}

TEST_F(NameStageTest, FirstOnlyValidation) {
    gm->updateField("name", "firstName", "John");
    bool expected = false;
    bool result = stage->validateStage();
    EXPECT_EQ(result, expected);
}

TEST_F(NameStageTest, LastOnlyValidation) {
    gm->updateField("name", "lastName", "Smith");
    bool expected = false;
    bool result = stage->validateStage();
    EXPECT_EQ(result, expected);
}

TEST_F(NameStageTest, SuccessfulValidation) {
    gm->updateField("name", "firstName", "John");
    gm->updateField("name", "lastName", "Smith");
    bool expected = true;
    bool result = stage->validateStage();
    EXPECT_EQ(result, expected);
}

