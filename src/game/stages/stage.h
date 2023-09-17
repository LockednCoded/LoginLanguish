/*!
    @file stage.h
    @brief the Stage class is an abstract class that represents a stage of the game
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#pragma once

#include <vector>
#include <string>
#include <map>
#include "rapidjson/document.h"

/*!
    @brief the Stage class is an abstract class that represents a stage in the game
    @details contains functions that are implemented by all stages in the game
*/
class Stage
{
public:
    virtual bool validateStage() = 0;
    std::vector<std::string> getFieldErrors(std::string field);
    virtual void update(const rapidjson::Value &req) = 0;
    std::string getStageName();
    rapidjson::Value getStageState(rapidjson::Document::AllocatorType &allocator);
    virtual rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator) = 0;
    virtual void progressStage() {};
    //TODO: implement this
    bool isFieldDisabled(std::string field) { return false; };
    // virtual void setFieldDisabled(std::string field, bool disabled) = 0;
protected:
    rapidjson::Value createFieldState(std::string field, rapidjson::Value &fieldValue, rapidjson::Document::AllocatorType &allocator);
    std::string name = "";
    std::map<std::string, std::vector<std::string>> field_errors;
    const int REQ_FIELD_INDEX = 1;
    const int REQ_VALUE_INDEX = 2;
};