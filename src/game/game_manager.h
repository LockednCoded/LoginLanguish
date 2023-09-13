#include <string>
#include <vector>
#include <map>
#include "stages/stage.h"


class GameManager
{
public:
    GameManager();
    std::string updateStage(std::string args);
    // std::string getStage();
    std::string getNextStage();
private:
    int stage_index;
    std::vector<Stage* > stages;

    Stage* current_stage;

};