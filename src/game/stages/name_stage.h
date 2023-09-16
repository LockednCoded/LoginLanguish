#pragma once

#include "stage.h"
#include "../game_manager.h"

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