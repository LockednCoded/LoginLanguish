#pragma once

#include "stage.h"
#include "../game_manager.h"

class NameStage : public Stage {
public:
    NameStage(GameManager *gameManager);

    bool validateStage();
    std::vector<std::string> getStageErrors(std::vector<std::string> args);
    void update(const rapidjson::Value &req);
    std::string getStageName();
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
protected:
    std::string name = "name";
    
private:
    GameManager* gm;
    std::string first_name = "";
    std::string last_name = "";
};