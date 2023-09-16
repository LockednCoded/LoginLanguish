#include "extras_stage.h"

ExtrasStage::ExtrasStage(GameManager *gameManager){
    gm = gameManager;
};

bool ExtrasStage::validateStage()
{
    return true;
}

std::vector<std::string> ExtrasStage::getStageErrors(std::vector<std::string> args)
{   
    std::vector<std::string> errors;
    return errors;
}

void ExtrasStage::update(const rapidjson::Value &req)
{
    std::string field = req[REQ_FIELD_INDEX].GetString();
    if (field.compare("dob") == 0)
        dob = req[REQ_VALUE_INDEX].GetString();
    else if (field.compare("tsAndCs") == 0) {
        ts_and_cs = req[REQ_VALUE_INDEX].GetBool();
    }
}

std::string ExtrasStage::getStageName()
{
    return "extras";
}

rapidjson::Value ExtrasStage::getFieldStates(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value fieldStates(rapidjson::kObjectType);

    rapidjson::Value dobValue(dob.c_str(), allocator);
    rapidjson::Value dobObj = createFieldState("dob", dobValue, allocator);
    fieldStates.AddMember("dob", dobObj, allocator);

    std::string tsAndCsStr = ts_and_cs ? "true" : "false";
    rapidjson::Value tsAndCsValue(tsAndCsStr.c_str(), allocator);
    rapidjson::Value tsAndCsObj = createFieldState("tsAndCs", tsAndCsValue, allocator);
    fieldStates.AddMember("tsAndCs", tsAndCsObj, allocator);

    return fieldStates;
};