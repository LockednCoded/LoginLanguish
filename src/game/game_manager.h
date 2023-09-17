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
#include "rapidjson/document.h"
// #include "stages/stage.h"

class Stage;

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
    void updateField(const std::string &stage, const std::string &field, const std::string &value);
    // std::string getStage();
    std::string getNextStage();
    std::vector<std::string> getFieldErrors(const std::string &stage, const std::string &field);
    rapidjson::Document getGameState();
    void progressStage(const rapidjson::Value &req);
    std::string getCurrentStageName();

private:
    std::map<std::string, Stage *> stages_map;
    int stage_index;
    std::vector<Stage* > stages;

    Stage* current_stage;
    const int REQ_STAGE_INDEX = 0;
};