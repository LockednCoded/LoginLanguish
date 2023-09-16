#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <rapidjson/document.h>
#include "game_manager.h"

#include "stages/image_captcha_stage.h"

namespace {
    class ImageCaptchaStageTest : public ::testing::Test {
        protected:
            GameManager *gm;
            ImageCaptchaStage *stage;

            ImageCaptchaStageTest() {}

            virtual ~ImageCaptchaStageTest() {}

            // set up a test environment before each test case
            virtual void SetUp() override {
                gm = new GameManager();
                stage = dynamic_cast<ImageCaptchaStage*>(gm->getStage("image_captcha"));
            }

            // tear down a test environment after each test case
            virtual void TearDown() override {
                delete stage;
                delete gm;
            }
    };
}

TEST_F(ImageCaptchaStageTest, SetSelected) {
    rapidjson::Document req;
    req.Parse("[\"image_captcha\", \"selected\", [1, 2, 3]]");
    rapidjson::Value reqArray = req.GetArray();
    gm->updateField(reqArray);
    std::vector<int> expected = {1, 2, 3};
    rapidjson::Document document;
    std::vector<int> result;
    rapidjson::Value resultArray = stage->getFieldStates(document.GetAllocator())["selected"].GetArray();
    for (int i = 0; i < (int) resultArray.Size(); i++) {
        result.push_back(resultArray[i].GetInt());
    }
    EXPECT_EQ(result, expected);
}