/*!
    @file extras_stage.h
    @brief the ExtrasStage class is the class that represents the extras stage of the game
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#pragma once

#include "stage.h"
#include "../game_manager.h"

/*!
    @brief the ExtrasStage class is a class that represents a extras stage in the game
    @details contains concrete stage implementions for the extras stage in the game
*/
class ExtrasStage : public Stage {
public:
    ExtrasStage(GameManager *gameManager);

    bool validateStage();
    void update(const rapidjson::Value &req);
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);

    // error messages
    std::string missingDobError = "Please enter your date of birth before continuing.";
    std::string tooYoungError = "You are too young to sign up. Please review our terms & conditions before continuing.";
    std::string tooOldError = "You are too old to sign up. Please review our terms & conditions before continuing.";
    std::string uncheckedTCsError = "Please review and accept our terms & conditions before continuing.";
private:
    void updateErrors(const std::string &field);

    std::vector<int> dob; // [0]day, [1]month, [2]year
    std::vector<int> solstice = {21, 6, 1984};
    bool ts_and_cs = false;
};