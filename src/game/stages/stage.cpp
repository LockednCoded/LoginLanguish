/*!
    @file stage.cpp
    @brief the implementation of the Stage class
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#include "stage.h"

Stage::Stage(GameManager *gameManager)
{
    this->gm = gameManager;
}

/*!
    @brief creates the JSON representation of the stage state
    @details this function creates rapidjson::Value object containing the stage state including
    the stage name and the JSON representation of the field states
    @param allocator the rapidjson::Document::AllocatorType object used to allocate memory for the JSON objects
    @return rapidjson value object containing the stage state
    @ref Stage::getFieldStates
*/
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

/*!
    @brief creates the JSON representation of the field states
    @details this function creates rapidjson::Value object containing the field states, this functions is used
    for standard fields that have a value, errors and disabled property
    @param field the name of the field to create the field state for
    @param fieldValue the rapidjson::Value object containing the field value (this may be any native type and is created by @ref Stage::getFieldStates)
    @param allocator the rapidjson::Document::AllocatorType object used to allocate memory for the JSON objects
    @return rapidjson value object containing the field states
*/
rapidjson::Value Stage::createFieldState(const std::string &field, rapidjson::Value &fieldValue, rapidjson::Document::AllocatorType &allocator)
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

/*!
    @brief gets the field errors for a given field
    @details this function returns the field errors for a given field
    @param field the field to get the errors for
    @return string vector containing the field errors
*/
std::vector<std::string> Stage::getFieldErrors(std::string field)
{
    return field_errors[field];
}

/*!
    @brief gets the stage name
    @details returns the stage name as a string
    @return string containing the stage name
*/
std::string Stage::getStageName()
{
    return name;
}

bool Stage::isFieldDisabled(const std::string &field)
{
    return gm->getCurrentStageName().compare(getStageName()) != 0;
}