#pragma once

#include "stage.h"

class CredentialsStage : public Stage {
public:
    bool validateStage();
    std::string getStageErrors(std::vector<std::string> args);
    void updateStage(std::vector<std::string> args);
    std::string getStageName();
    rapidjson::Value getStageState(rapidjson::Document::AllocatorType &allocator);

private:
    std::string username;
    std::string password;
};