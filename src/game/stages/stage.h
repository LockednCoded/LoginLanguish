#pragma once

#include <vector>
#include <string>
#include "rapidjson/document.h"

class Stage
{
public:
    virtual bool validateStage() = 0;
    virtual std::vector<std::string> getStageErrors(std::vector<std::string> args) = 0;
    virtual void updateField(std::string field, std::string value) = 0;
    virtual std::string getStageName() = 0;
    rapidjson::Value getStageState(rapidjson::Document::AllocatorType &allocator);
    
    //TODO: implement this
    bool isFieldDisabled(std::string field) { return false; };
    // virtual void setFieldDisabled(std::string field, bool disabled) = 0;
protected:
    rapidjson::Value createFieldState(std::string field, rapidjson::Value &fieldValue, rapidjson::Document::AllocatorType &allocator);
    virtual rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator) = 0;
};