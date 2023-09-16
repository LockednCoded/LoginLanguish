#include "game_manager.h"
#include "stages/name_stage.h"
#include "stages/credentials_stage.h"
#include "stages/txt_captcha_stage.h"
#include "stages/extras_stage.h"
#include "stages/image_captcha_stage.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include <rapidjson/writer.h>

#include <iostream>

GameManager::GameManager()
{
    stage_index = 0;

    Stage *name_stage = new NameStage(this);
    Stage *credentials_stage = new CredentialsStage(this);
    Stage *extras_stage = new ExtrasStage(this);
    Stage *txt_captcha_stage = new TxtCaptchaStage(this);
    Stage *image_captcha_stage = new ImageCaptchaStage(this);

    stages.push_back(name_stage);
    stages.push_back(credentials_stage);
    stages.push_back(extras_stage);
    stages.push_back(txt_captcha_stage);
    stages.push_back(image_captcha_stage);

    stages_map["name"] = name_stage;
    stages_map["credentials"] = credentials_stage;
    stages_map["extras"] = extras_stage;
    stages_map["txt_captcha"] = txt_captcha_stage;
    stages_map["image_captcha"] = image_captcha_stage;

    current_stage = stages[stage_index];
}

Stage* GameManager::getStage(std::string stage)
{
    return stages_map[stage];
}

std::string GameManager::getNextStage()
{
    if (stage_index == stages.size() - 1)
    {
        return "end";
    }
    current_stage = stages[++stage_index];
    return current_stage->getStageName();
}

void GameManager::updateField(const rapidjson::Value &req)
{
    const char *index = req[REQ_STAGE_INDEX].GetString();
    stages_map[index]->update(req);
}

void GameManager::updateField(std::string stage, std::string field, std::string value)
{
    rapidjson::Document document;
    document.SetArray();
    rapidjson::Document::AllocatorType &allocator = document.GetAllocator();

    document.PushBack(rapidjson::Value(stage.c_str(), allocator), allocator);
    document.PushBack(rapidjson::Value(field.c_str(), allocator), allocator);
    document.PushBack(rapidjson::Value(value.c_str(), allocator), allocator);

    rapidjson::Value req = document.GetArray();
    updateField(req);
}

std::vector<std::string> GameManager::getFieldErrors(std::string stage, std::string field) {
    return stages_map[stage]->getFieldErrors(field);
}

rapidjson::Document GameManager::getGameState()
{
    rapidjson::Document document;
    document.SetObject();

    rapidjson::Value currentStage(current_stage->getStageName().c_str(), document.GetAllocator());
    document.AddMember("stage", currentStage, document.GetAllocator());

    // TODO: check if stage can progress
    document.AddMember("canProgress", true, document.GetAllocator());

    rapidjson::Value stagesArray(rapidjson::kArrayType);
    for (auto stage : stages)
    {
        rapidjson::Value stageState = stage->getStageState(document.GetAllocator());
        stagesArray.PushBack(stageState, document.GetAllocator());
    }

    document.AddMember("stages", stagesArray, document.GetAllocator());
    return document;
}