/*!
    @file end_stage.cpp
    @brief the implementation of the EndStage class
    @author Cameron Brue
    @copyright 2023 Locked & Coded
*/

#include "end_stage.h"

/*!
    @brief constructor for ImageCaptchaStage
    @param gameManager the game manager object owning this stage
*/
EndStage::EndStage(GameManager *gameManager) : Stage(gameManager)
{
    name = "end";
};

/*!
    @brief validates the stage
    @details validates the stage by checking if the requirements are met
    @return true if the stage is valid, false otherwise
*/
bool EndStage::validateStage()
{
    return false;
}

/*!
    @brief updates the stage
    @details updates the stage by updating the field values
    @param req the request object containing the field to update and the new value
*/
void EndStage::update(const rapidjson::Value &req)
{

}

/*!
    @brief gets the field states
    @details gets the field states by returning a rapidjson object containing the field states
    @param allocator the rapidjson allocator
    @return the rapidjson object containing the field states
*/
rapidjson::Value EndStage::getFieldStates(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value fieldStates(rapidjson::kObjectType);
    return fieldStates;
};