#include <string>
#include <vector>
#include <map>
#include "stages/stage.h"


class GameManager
{
public:
    GameManager();
    void updateField(const rapidjson::Value &req);
    // std::string getStage();
    std::string getNextStage();
    std::vector<std::string> getStageErrors(std::vector<std::string> args);
    rapidjson::Document getGameState();

private:
    std::map<std::string, Stage *> stages_map;
    int stage_index;
    std::vector<Stage* > stages;

    Stage* current_stage;
    const int REQ_STAGE_INDEX = 0;
};