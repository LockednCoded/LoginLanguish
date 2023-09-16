#include "stage.h"

rapidjson::Value Stage::getStageState(rapidjson::Document::AllocatorType &allocator)
{
    //create stage state object
    rapidjson::Value stageState(rapidjson::kObjectType);

    //add stage name to stage state object
    rapidjson::Value stageName(getStageName().c_str(), allocator);
    stageState.AddMember("name", stageName, allocator);

    //add fields states to stage state object
    rapidjson::Value fieldStates = getFieldStates(allocator);
    stageState.AddMember("state", fieldStates, allocator);

    return stageState;
}

rapidjson::Value Stage::createFieldState(std::string field, rapidjson::Value &fieldValue, rapidjson::Document::AllocatorType &allocator)
{
    // create field state object
    rapidjson::Value fieldState(rapidjson::kObjectType);

    // add already created field value object to field state object
    fieldState.AddMember("value", fieldValue, allocator);

    //add errors to field state object
    rapidjson::Value fieldErrors(rapidjson::kArrayType);
    for (auto error : getFieldErrors(field))
    {
        rapidjson::Value errorValue(error.c_str(), allocator);
        fieldErrors.PushBack(errorValue, allocator);
    }
    fieldState.AddMember("errors", fieldErrors, allocator);

    //add disabled prop to field state object
    fieldState.AddMember("disabled", rapidjson::Value(isFieldDisabled(field)), allocator);

    return fieldState;
}

std::vector<std::string> Stage::getFieldErrors(std::string field)
{
    return field_errors[field];
}

std::string Stage::getStageName()
{
    return name;
}
