/*!
    @file name_stage.h
    @brief The ExtrasStage class is a class that represents the name stage in the game
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#pragma once

#include "stage.h"
#include "../game_manager.h"

/*!
    @brief The NameStage class is a class that represents a name stage in the game.
    @details The NameStage class is a class that represents a name stage in the game. It contains
    concrete stage implementions for the name stage in the game.
*/
class NameStage : public Stage {
public:
    NameStage(GameManager *gameManager);

    bool validateStage();
    void update(const rapidjson::Value &req);
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
private:
    void updateErrors(std::string field);

    GameManager* gm;
    std::string first_name = "";
    std::string last_name = "";
};