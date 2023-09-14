#include "game_manager.h"
#include "stages/name_stage.h"
#include "stages/credentials_stage.h"
#include "stages/details_stage.h"
#include "stages/txt_captcha_stage.h"
#include "rapidjson/document.h"

GameManager::GameManager()
{
    stage_index = 0;
    stages.push_back(new NameStage());
    stages.push_back(new CredentialsStage());
    stages.push_back(new DetailsStage());
    stages.push_back(new TxtCaptchaStage());
    current_stage = stages[stage_index];
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

void GameManager::updateStage(std::vector<std::string> args)
{
    current_stage->updateStage(args);
}

std::string GameManager::getStageErrors(std::vector<std::string> args) {
    return current_stage->getStageErrors(args);
}

rapidjson::Document GameManager::getGameState()
{
    rapidjson::Document document;
    document.SetObject();
    for (auto stage : stages)
    {
        rapidjson::Value stageState = stage->getStageState(document.GetAllocator());
        document.AddMember(rapidjson::StringRef(stage->getStageName().c_str()), stageState, document.GetAllocator());
    }
    return document;
}