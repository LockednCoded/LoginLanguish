#pragma once

#include "stage.h"

class DetailsStage : public Stage {
public:
    bool validateStage();
    std::vector<std::string> getStageErrors(std::vector<std::string> args);
    void updateField(std::string field, std::string value);
    std::string getStageName();
protected:
    std::string name = "details";
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
private:
    std::string username = "";
    std::string password = "";
};