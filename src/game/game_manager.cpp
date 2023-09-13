#include "game_manager.h"
#include "stages/name_stage.h"
#include "stages/credentials_stage.h"
#include "stages/details_stage.h"
#include "stages/txt_captcha_stage.h"


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

std::string GameManager::updateStage(std::string args)
{
    return "true";
}