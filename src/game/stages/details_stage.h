#pragma once

#include "stage.h"

class DetailsStage : public Stage {
public:
    bool validateStage();
    std::vector<std::string> getStageErrors(std::vector<std::string> args);
    void updateStage(std::vector<std::string> args);
    std::string getStageName();
    rapidjson::Value getStageState(rapidjson::Document::AllocatorType &allocator);
protected:
    std::string name = "details";
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
private:
    std::string username = "";
    std::string password = "";
};