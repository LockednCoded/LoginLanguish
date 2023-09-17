/*!
    @file game_manager.h
    @brief the GameManager class is the class that controls the flow of the game
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#pragma once

#include <string>
#include <vector>
#include <map>
#include "stages/stage.h"

/*!
    @brief the GameManager class is a class that controls the flow of the game
    @details contains all concrete stage objects and method for interacting with the vairous stages
*/
class GameManager
{
public:
    GameManager();
    Stage* getStage(std::string stage);
    void updateField(const rapidjson::Value &req);
    void updateField(std::string stage, std::string field, std::string value);
    // std::string getStage();
    std::string getNextStage();
    std::vector<std::string> getFieldErrors(std::string stage, std::string field);
    rapidjson::Document getGameState();
    void progressStage(const rapidjson::Value &req);

private:
    std::map<std::string, Stage *> stages_map;
    int stage_index;
    std::vector<Stage* > stages;

    Stage* current_stage;
    const int REQ_STAGE_INDEX = 0;
};