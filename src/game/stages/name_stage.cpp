/*!
    @file name_stage.cpp
    @brief the implementation of the NameStage class
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#include "name_stage.h"

/*!
    @brief constructor for NameStage
    @param gameManager the game manager object owning this stage
*/
NameStage::NameStage(GameManager *gameManager) : Stage(gameManager)
{
    name = "name";
    field_errors = {
        {"firstName", std::vector<std::string>()},
        {"lastName", std::vector<std::string>()}
    };
}

/*!
    @brief validates the stage
    @details validates the stage by checking if the requirements are met
    @return true if the stage is valid, false otherwise
*/
bool NameStage::validateStage()
{
    int numErrors = field_errors["firstName"].size() + field_errors["lastName"].size();
    if (numErrors == 0 && first_name.length() > 0 && last_name.length() > 0)
        return true;
    return false;
}

/*!
    @brief updates error messages
    @details updates the error messages for the given field
    @param field the name of the field to update
*/
void NameStage::updateErrors(const std::string &field)
{   
    std::vector<std::string> errors;

    std::string invalidChars = "!@#$%^&*()_=+[]{}\\|;:\",.<>/?`~";

    if (field.compare("firstName") == 0){
        if (first_name.length() == 0){
            // do nothing
        } else if (first_name.length() > 12){
            errors.push_back(fNameLengthError);
        } else if (first_name.find_first_of(invalidChars) != std::string::npos){
            errors.push_back(fNameInvalidCharError);
        }

        field_errors["firstName"] = errors;

    } else if (field.compare("lastName") == 0){
        if (last_name.length() == 0){
            // do nothing
        } else if (last_name.length() > 12){
            errors.push_back(lNameLengthError);
        } else if (last_name.find_first_of(invalidChars) != std::string::npos){
            errors.push_back(lNameInvalidCharError);
        }

        field_errors["lastName"] = errors;
    }
}

/*!
    @brief updates the stage
    @details updates the stage by updating the field values
    @param req the request object containing the field to update and the new value
*/
void NameStage::update(const rapidjson::Value &req)
{
    std::string field = req[REQ_FIELD_INDEX].GetString();
    if (field.compare("firstName") == 0)
        first_name = req[REQ_VALUE_INDEX].GetString();
    else if (field.compare("lastName") == 0)
        last_name = req[REQ_VALUE_INDEX].GetString();
    
    updateErrors(field);
}

/*!
    @brief gets the field states
    @details gets the field states by returning a rapidjson object containing the field states
    @param allocator the allocator object to use for creating the rapidjson object
    @return a rapidjson object containing the field states
*/
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

