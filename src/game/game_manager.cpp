#include "game_manager.h"


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