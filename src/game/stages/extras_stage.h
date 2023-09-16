#pragma once

#include "stage.h"
#include "../game_manager.h"

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