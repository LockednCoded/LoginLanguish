/*!
    @file extras_stage.h
    @brief The ExtrasStage class is a class that represents the extras stage in the game
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#pragma once

#include "stage.h"
#include "../game_manager.h"

/*!
    @brief The ExtrasStage class is a class that represents a extras stage in the game.
    @details The ExtrasStage class is a class that represents a extras stage in the game. It contains
    concrete stage implementions for the extras stage in the game.
*/
class ExtrasStage : public Stage {
public:
    ExtrasStage(GameManager *gameManager);

    bool validateStage();
    void update(const rapidjson::Value &req);
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
private:
    void updateErrors(std::string field);

    GameManager* gm;
    std::string dob = "";
    bool ts_and_cs = false;
};