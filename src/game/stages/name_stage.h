#pragma once

#include "stage.h"

class NameStage : public Stage {
public:
    bool validateStage();
    std::string getStageErrors(std::vector<std::string> args);
    void updateStage(std::vector<std::string> args);
    std::string getStageName();
    rapidjson::Value getStageState(rapidjson::Document::AllocatorType &allocator);

private:
    std::string first_name;
    std::string last_name;
};