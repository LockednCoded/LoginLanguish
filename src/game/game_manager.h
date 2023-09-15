#include <string>
#include <vector>
#include <map>
#include "stages/stage.h"


class GameManager
{
public:
    GameManager();
    void updateStage(std::vector<std::string> args);
    // std::string getStage();
    std::string getNextStage();
    std::vector<std::string> getStageErrors(std::vector<std::string> args);
    rapidjson::Document getGameState();

private:
    int stage_index;
    std::vector<Stage* > stages;

    Stage* current_stage;

};