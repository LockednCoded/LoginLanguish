#include "game_manager.h"

std::string GameManager::getNextStage()
{
    if (current_stage == stages.size() - 1)
    {
        return "end";
    }
    return stages[++current_stage];
}

std::string GameManager::submitStage(std::string args)
{
    return "true";
}