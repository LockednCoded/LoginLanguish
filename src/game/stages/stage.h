#pragma once

#include <vector>
#include <string>
#include "rapidjson/document.h"

class Stage
{
public:
    virtual bool validateStage() = 0;
    virtual std::vector<std::string> getStageErrors(std::vector<std::string> args) = 0;
    virtual void updateStage(std::vector<std::string> args) = 0;
    virtual std::string getStageName() = 0;
    virtual rapidjson::Value getStageState(rapidjson::Document::AllocatorType &allocator) = 0;

protected:
    bool stage_completed = false;
};