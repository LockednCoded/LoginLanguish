#include "name_stage.h"

bool NameStage::validateStage()
{
    return true;
}

std::vector<std::string> NameStage::getStageErrors(std::vector<std::string> args)
{   
    std::vector<std::string> errors;
    return errors;
}

void NameStage::updateField(std::string field, std::string value)
{
    if (field.compare("firstName") == 0)
        first_name = value;
    else if (field.compare("lastName") == 0)
        last_name = value;
}

std::string NameStage::getStageName()
{
    return "name";
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