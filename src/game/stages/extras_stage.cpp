/*!
    * @file extras_stage.cpp
    * @brief This file contains the implementation of the ExtrasStage class.
    * @author Cameron Brue
    * @copyright 2023 Locked & Coded
*/

#include "extras_stage.h"

/*!
    @brief constructor for ExtrasStage
    @param gameManager the game manager object owning this stage
*/
ExtrasStage::ExtrasStage(GameManager *gameManager){
    name = "extras";
    gm = gameManager;
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
    return true;
}

/*!
    @brief updates error messages
    @details updates the error messages for the given field
    @param field the name of the field to update
*/
void ExtrasStage::updateErrors(std::string field)
{   
    //TODO: implement this
}

/*!
    @brief updates the stage
    @details updates the stage by updating the field values
    @param req the request object containing the field to update and the new value
*/
void ExtrasStage::update(const rapidjson::Value &req)
{
    std::string field = req[REQ_FIELD_INDEX].GetString();
    if (field.compare("dob") == 0)
        dob = req[REQ_VALUE_INDEX].GetString();
    else if (field.compare("tsAndCs") == 0) {
        ts_and_cs = req[REQ_VALUE_INDEX].GetBool();
    }

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

    rapidjson::Value dobValue(dob.c_str(), allocator);
    rapidjson::Value dobObj = createFieldState("dob", dobValue, allocator);
    fieldStates.AddMember("dob", dobObj, allocator);

    rapidjson::Value tsAndCsValue(ts_and_cs);
    rapidjson::Value tsAndCsObj = createFieldState("tsAndCs", tsAndCsValue, allocator);
    fieldStates.AddMember("tsAndCs", tsAndCsObj, allocator);

    return fieldStates;
};