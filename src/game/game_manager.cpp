/*!
    @file game_manager.cpp
    @brief the implementation of the GameManager class
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#include "game_manager.h"
#include "stages/name_stage.h"
#include "stages/credentials_stage.h"
#include "stages/txt_captcha_stage.h"
#include "stages/extras_stage.h"
#include "stages/image_captcha_stage.h"
#include "stages/end_stage.h"
#include "stages/dwayne_stage.h"
#include "rapidjson/stringbuffer.h"
#include <rapidjson/writer.h>
#include "preprocessor_vars.h"

#include <iostream>

/*!
    @brief constructor for GameManager
*/
GameManager::GameManager()
{
    stage_index = 0;

    Stage *name_stage = new NameStage(this);
    Stage *credentials_stage = new CredentialsStage(this);
    Stage *extras_stage = new ExtrasStage(this);
    Stage *txt_captcha_stage = new TxtCaptchaStage(this);
    Stage *image_captcha_stage = new ImageCaptchaStage(this);
    Stage *dwayne_stage = new DwayneStage(this);
    Stage *end_stage = new EndStage(this);

    stages.push_back(name_stage);
    stages.push_back(credentials_stage);
    stages.push_back(extras_stage);
    stages.push_back(txt_captcha_stage);
    stages.push_back(image_captcha_stage);
    stages.push_back(dwayne_stage);
    stages.push_back(end_stage);

    stages_map["name"] = name_stage;
    stages_map["credentials"] = credentials_stage;
    stages_map["extras"] = extras_stage;
    stages_map["txtcaptcha"] = txt_captcha_stage;
    stages_map["imagecaptcha"] = image_captcha_stage;
    stages_map["dwayne"] = dwayne_stage;
    stages_map["end"] = end_stage;

    current_stage = stages[stage_index];
}

/*!
    @brief gets the current stage
    @param stage name of stage requested
    @return pointer to stage
*/
Stage *GameManager::getStage(std::string stage)
{
    return stages_map[stage];
}

/*!
    @brief progresses to the next stage is current stage is validated
    @return "no" if current stage is not validated, "end" if it is the end, or the name of the new stage
*/
std::string GameManager::getNextStage()
{
    if (!current_stage->validateStage() && !__CHEAT_MODE__)
        return "no";
    if (stage_index == stages.size() - 1)
        return "end";
    current_stage = stages[++stage_index];
    return current_stage->getStageName();
}

/*!
    @brief updates the field
    @details updates the field within the requested stage
    @param req the request object containing the stage, field to update and the new value
    @ref Stage::update
*/
void GameManager::updateField(const rapidjson::Value &req)
{
    const char *index = req[REQ_STAGE_INDEX].GetString();
    stages_map[index]->update(req);
}

/*!
    @brief updates the field
    @details helper method to update the field within the requested stage, using string instead
    of a rapidjson object, used in testing
    @param stage the name of the stage to update
    @param field the name of the field to update
    @param value the new value of the field
    @ref GameManager::updateField
*/
void GameManager::updateField(const std::string &stage, const std::string &field, const std::string &value)
{
    rapidjson::Document document;
    document.SetArray();
    rapidjson::Document::AllocatorType &allocator = document.GetAllocator();

    document.PushBack(rapidjson::Value(stage.c_str(), allocator), allocator);
    document.PushBack(rapidjson::Value(field.c_str(), allocator), allocator);
    document.PushBack(rapidjson::Value(value.c_str(), allocator), allocator);

    rapidjson::Value &req = document.GetArray();
    updateField(req);
}

/*!
    @brief gets the field errors
    @details gets the field errors for the requested stage and field
    @param stage the name of the stage to get the field errors for
    @param field the name of the field to get the errors for
    @return a vector of strings containing the errors for the field
    @ref Stage::getFieldErrors
*/
std::vector<std::string> GameManager::getFieldErrors(const std::string &stage, const std::string &field)
{
    return stages_map[stage]->getFieldErrors(field);
}

std::string GameManager::getCurrentStageName()
{
    return current_stage->getStageName();
}

/*!
    @brief gets the game state
    @details gets the game state by creating a rapidjson object containing the game state
    @return a rapidjson object containing the game state
    @ref Stage::getStageState
*/
rapidjson::Document GameManager::getGameState()
{
    bool canProgress = false;
    if (current_stage->validateStage() || __CHEAT_MODE__)
        canProgress = true;

    rapidjson::Document document;
    document.SetObject();

    rapidjson::Value currentStage(current_stage->getStageName().c_str(), document.GetAllocator());
    document.AddMember("stage", currentStage, document.GetAllocator());

    document.AddMember("canProgress", canProgress, document.GetAllocator());

    rapidjson::Value stagesArray(rapidjson::kArrayType);
    for (auto stage : stages)
    {
        rapidjson::Value stageState = stage->getStageState(document.GetAllocator());
        stagesArray.PushBack(stageState, document.GetAllocator());
    }

    document.AddMember("stages", stagesArray, document.GetAllocator());
    return document;
}

void GameManager::progressStage(const rapidjson::Value &req)
{
    const char *index = req[REQ_STAGE_INDEX].GetString();
    stages_map[index]->progressStage();
}