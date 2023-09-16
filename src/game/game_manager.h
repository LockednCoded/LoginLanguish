#pragma once

#include <string>
#include <vector>
#include <map>
#include "stages/stage.h"


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

private:
    std::map<std::string, Stage *> stages_map;
    int stage_index;
    std::vector<Stage* > stages;

    Stage* current_stage;
    const int REQ_STAGE_INDEX = 0;
};