#include <string>
#include <vector>
#include <map>
#include "stages/stage.h"
#include "stages/name_stage.h"


class GameManager
{
public:
    std::string updateStage(std::string args);
    // std::string getStage();
    std::string getNextStage();
private:
    int stage_index = 0;
    std::vector<Stage* > stages = {&NameStage()};

    Stage* current_stage = stages[stage_index];
};