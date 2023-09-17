/*!
    @file end_stage.h
    @brief the EndStage class is the class that represents the end stage of the game
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#pragma once

#include "stage.h"
#include "../game_manager.h"

/*!
    @brief the EndStage class is a class that represents the end stage in the game
    @details contains concrete stage implementions for the end stage in the game
*/
class EndStage : public Stage {
public:
    EndStage(GameManager *gameManager);

    bool validateStage();
    void update(const rapidjson::Value &req);
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);

private:
    GameManager* gm;
};