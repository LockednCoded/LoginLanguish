/*!
    @file name_stage_test.cpp
    @brief the unit tests for the NameStage class
    @author Cameron Bruce
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