#include "name_stage.h"

NameStage::NameStage(GameManager *gameManager){
    name = "name";
    gm = gameManager;
    field_errors = {
        {"firstName", std::vector<std::string>()},
        {"lastName", std::vector<std::string>()}
    };
}

bool NameStage::validateStage()
{
    return true;
}

void NameStage::updateErrors(std::string field)
{   
    //TODO: implement this?
}

void NameStage::update(const rapidjson::Value &req)
{
    std::string field = req[REQ_FIELD_INDEX].GetString();
    if (field.compare("firstName") == 0)
        first_name = req[REQ_VALUE_INDEX].GetString();
    else if (field.compare("lastName") == 0)
        last_name = req[REQ_VALUE_INDEX].GetString();
    
    updateErrors(field);
}

rapidjson::Value NameStage::getFieldStates(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value fieldStates(rapidjson::kObjectType);

    rapidjson::Value firstNameValue(first_name.c_str(), allocator);
    rapidjson::Value firstNameObj = createFieldState("firstName", firstNameValue, allocator);
    fieldStates.AddMember("firstName", firstNameObj, allocator);

    rapidjson::Value lastNameValue(last_name.c_str(), allocator);
    rapidjson::Value lastNameObj = createFieldState("lastName", lastNameValue, allocator);
    fieldStates.AddMember("lastName", lastNameObj, allocator);

    return fieldStates;
};

