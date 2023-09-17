/*!
    @file extras_stage.cpp
    @brief the implementation of the ExtrasStage class.
    @author Cameron Brue
    @copyright 2023 Locked & Coded
*/

#include "extras_stage.h"

/*!
    @brief constructor for ExtrasStage
    @param gameManager the game manager object owning this stage
*/
ExtrasStage::ExtrasStage(GameManager *gameManager) : Stage(gameManager)
{
    name = "extras";
    field_errors = {
        {"dob", std::vector<std::string>()},
        {"tsAndCs", std::vector<std::string>()}
    };
}

/*!
    @brief validates the stage
    @details validates the stage by checking if the requirements are met
    @return true if the stage is valid, false otherwise
*/
bool ExtrasStage::validateStage()
{
    int numErrors = field_errors["dob"].size() + field_errors["tsAndCs"].size();
    if (numErrors == 0 && dob.size() == 3 && ts_and_cs)
        return true;
    return false;
}

/*!
    @brief updates error messages
    @details updates the error messages for the given field
    @param field the name of the field to update
*/
void ExtrasStage::updateErrors(std::string field)
{   
    std::vector<std::string> errors;
    if (field.compare("dob") == 0){
        if (dob.size() == 0)
            errors.push_back(missingDobError);
        else if (dob[2] == solstice[2]){                // check year
            if (dob[1] == solstice[1]){                 // check month
                if (dob[0] == solstice[0]){             // check date
                    // do nothing
                } else if (dob[0] > solstice[0])
                    errors.push_back(tooYoungError);
                else if (dob[0] < solstice[0])
                    errors.push_back(tooOldError);
            }
            else if (dob[1] > solstice[1])
                errors.push_back(tooYoungError);
            else if (dob[1] < solstice[1])
                errors.push_back(tooOldError);
        }
        else if (dob[2] > solstice[2])
            errors.push_back(tooYoungError);
        else if (dob[2] < solstice[2])
            errors.push_back(tooOldError);

        field_errors["dob"] = errors;
    }
    else if (field.compare("tsAndCs") == 0){
        if (!ts_and_cs)
            errors.push_back(uncheckedTCsError);

        field_errors["tsAndCs"] = errors;
    }
}

/*!
    @brief updates the stage
    @details updates the stage by updating the field values
    @param req the request object containing the field to update and the new value
*/
void ExtrasStage::update(const rapidjson::Value &req)
{
    std::string field = req[REQ_FIELD_INDEX].GetString();

    if (field.compare("dob") == 0) {
        std::vector<int> new_dob = {0, 0, 0};
        int inputSize = req[REQ_VALUE_INDEX].Size();
        if (inputSize != 3)
        {
            new_dob = std::vector<int>();
        }
        else
        {
            for (size_t i = 0; i < 3; i++)
            {
                new_dob[i] = req[REQ_VALUE_INDEX][i].GetInt();
            }
        }
        dob = new_dob;
    }
    else if (field.compare("tsAndCs") == 0)
        ts_and_cs = req[REQ_VALUE_INDEX].GetBool();

    updateErrors(field);
}

/*!
    @brief gets the field states
    @details gets the field states by creating a rapidjson object containing the field states
    @param allocator the rapidjson allocator
    @return the rapidjson object containing the field states
    @ref Stage::createFieldState
*/
rapidjson::Value ExtrasStage::getFieldStates(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value fieldStates(rapidjson::kObjectType);

    rapidjson::Value dobValue(rapidjson::kArrayType);
    for (size_t i = 0; i < dob.size(); i++) {
        dobValue.PushBack(dob[i], allocator);
    }
    rapidjson::Value dobObj = createFieldState("dob", dobValue, allocator);
    fieldStates.AddMember("dob", dobObj, allocator);

    rapidjson::Value tsAndCsValue(ts_and_cs);
    rapidjson::Value tsAndCsObj = createFieldState("tsAndCs", tsAndCsValue, allocator);
    fieldStates.AddMember("tsAndCs", tsAndCsObj, allocator);

    return fieldStates;
};