#pragma once

#include "stage.h"

class ExtrasStage : public Stage {
public:
    bool validateStage();
    std::vector<std::string> getStageErrors(std::vector<std::string> args);
    void update(const rapidjson::Value &req);
    std::string getStageName();
protected:
    //TODO: tidy up
    std::string name = "extras";
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
private:
    std::string dob = "";
    bool ts_and_cs = false;
};