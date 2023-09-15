#pragma once

#include "stage.h"

class CredentialsStage : public Stage {
public:
    bool validateStage();
    std::vector<std::string> getStageErrors(std::vector<std::string> args);
    void update(const rapidjson::Value &req);
    std::string getStageName();
protected:
    std::string name = "credentials";
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
private:
    std::string username = "";
    std::string password = "";
};