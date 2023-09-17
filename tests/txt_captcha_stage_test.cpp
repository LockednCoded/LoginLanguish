/*!
    @file txt_captcha_stage_test.cpp
    @brief the unit tests for the TextCaptchaStage class
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <rapidjson/document.h>
#include "game_manager.h"

#include "stages/txt_captcha_stage.h"

namespace {
    class TxtCaptchaStageTest : public ::testing::Test {
        protected:
            GameManager *gm;
            TxtCaptchaStage *stage;

            TxtCaptchaStageTest() {}

            virtual ~TxtCaptchaStageTest() {}

            // set up a test environment before each test case
            virtual void SetUp() override {
                gm = new GameManager();
                stage = dynamic_cast<TxtCaptchaStage*>(gm->getStage("txt_captcha"));
            }

            // tear down a test environment after each test case
            virtual void TearDown() override {
                delete stage;
                delete gm;
            }
    };
}


// TEXT CAPTCHA UNIT TESTS

// TEST_F(TxtCaptchaStageTest, SetTxtCaptcha) {
//     gm->updateField("txt_captcha", "txtcaptcha", "John");
//     std::string expected = "John";
//     rapidjson::Document document;
//     std::string result = stage->getFieldStates(document.GetAllocator())["txtcaptcha"]["value"].GetString();
//     EXPECT_EQ(result, expected);
// }