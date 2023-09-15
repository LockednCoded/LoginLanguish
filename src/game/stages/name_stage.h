#pragma once

#include "stage.h"

class NameStage : public Stage {
public:
    bool validateStage();
    std::vector<std::string> getStageErrors(std::vector<std::string> args);
    void updateField(std::string field, std::string value);
    std::string getStageName();
protected:
    std::string name = "name";
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
private:
    std::string first_name = "";
    std::string last_name = "";
};