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

TEST_F(ExtrasStageTest, SetDob) {
    gm->updateField("extras", "dob", "2023-12-12");
    std::string expected = "2023-12-12";
    rapidjson::Document document;
    std::string result = stage->getFieldStates(document.GetAllocator())["dob"]["value"].GetString();
    EXPECT_EQ(result, expected);
}

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