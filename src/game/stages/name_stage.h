/*!
    @file name_stage.h
    @brief the ExtrasStage class is the class that represents the DOB and T&Cs stage of the game
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#pragma once

#include "stage.h"
#include "../game_manager.h"

/*!
    @brief the NameStage class is a class that represents a name stage in the game
    @details contains concrete stage implementions for the name stage in the game
*/
class NameStage : public Stage {
public:
    NameStage(GameManager *gameManager);

    bool validateStage();
    void update(const rapidjson::Value &req);
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);

    // name error messages
    std::string firstLengthError = "First name must be between 2 and 24 characters in length.";
    std::string firstInvalidCharError = "Invalid characters in first name.";
    std::string lastLengthError = "Last name must be between 2 and 24 characters in length.";
    std::string lastInvalidCharError = "Invalid characters in last name.";

private:
    void updateErrors(std::string field);

    GameManager* gm;
    std::string first_name = "";
    std::string last_name = "";
};