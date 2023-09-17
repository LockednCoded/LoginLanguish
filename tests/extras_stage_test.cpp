/*!
    @file extras_stage_test.cpp
    @brief the unit tests for the ExtrasStage class
    @author Cameron Bruce, Jack Searle
    @copyright 2023 Locked & Coded
*/

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <rapidjson/document.h>
#include "game_manager.h"

#include "stages/extras_stage.h"

namespace {
    class ExtrasStageTest : public ::testing::Test {
        protected:
            GameManager *gm;
            ExtrasStage *stage;

            ExtrasStageTest() {}

            virtual ~ExtrasStageTest() {}

            // set up a test environment before each test case
            virtual void SetUp() override {
                gm = new GameManager();
                stage = dynamic_cast<ExtrasStage*>(gm->getStage("extras"));
            }

            // tear down a test environment after each test case
            virtual void TearDown() override {
                delete stage;
                delete gm;
            }
    };
}


// DOB UNIT TESTS

TEST_F(ExtrasStageTest, SetDob) {
    rapidjson::Document req;
    req.Parse("[\"extras\", \"dob\", {12, 12, 2023}]");
    rapidjson::Value &reqArray = req.GetArray();
    gm->updateField(reqArray);
    rapidjson::Document document;
    std::vector<int> result;
    rapidjson::Value &resultArray = stage->getFieldStates(document.GetAllocator())["selected"].GetArray();
    for (int i = 0; i < (int)resultArray.Size(); i++) {
        result.push_back(resultArray[i].GetInt());
    }
    std::vector<int> expected = {12, 12, 2023};
    EXPECT_EQ(result, expected);
}


// T&CS UNIT TESTS

TEST_F(ExtrasStageTest, SetTsAndCs) {
    rapidjson::Document req;
    req.Parse("[\"extras\", \"tsAndCs\", true]");
    rapidjson::Value &reqArray = req.GetArray();
    gm->updateField(reqArray);
    bool expected = true;
    rapidjson::Document document;
    bool result = stage->getFieldStates(document.GetAllocator())["tsAndCs"]["value"].GetBool();
    EXPECT_EQ(result, expected);
}