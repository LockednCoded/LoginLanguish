#pragma once

#include "stage.h"
#include "../game_manager.h"

class ExtrasStage : public Stage {
public:
    ExtrasStage(GameManager *gameManager);

    bool validateStage();
    std::vector<std::string> getStageErrors(std::vector<std::string> args);
    void update(const rapidjson::Value &req);
    std::string getStageName();
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
protected:
    //TODO: tidy up
    std::string name = "extras";
    
private:
    GameManager* gm;
    std::string dob = "";
    bool ts_and_cs = false;
};