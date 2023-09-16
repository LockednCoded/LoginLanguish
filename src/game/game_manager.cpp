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
    int index = req[REQ_STAGE_INDEX].GetInt();
    stages[index]->update(req);
}

std::vector<std::string> GameManager::getStageErrors(std::vector<std::string> args) {
    return current_stage->getStageErrors(args);
}

rapidjson::Document GameManager::getGameState()
{
    rapidjson::Document document;
    document.SetObject();

    rapidjson::Value currentStage(stage_index + 1);
    document.AddMember("stage", currentStage, document.GetAllocator());

    rapidjson::Value stagesArray(rapidjson::kArrayType);
    for (auto stage : stages)
    {
        rapidjson::Value stageState = stage->getStageState(document.GetAllocator());
        stagesArray.PushBack(stageState, document.GetAllocator());
    }

    document.AddMember("stages", stagesArray, document.GetAllocator());
    return document;
}