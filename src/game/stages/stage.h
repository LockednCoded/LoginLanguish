#pragma once

#include <vector>
#include <string>

class Stage
{
public:
    virtual bool validateStage() = 0;
    virtual std::string getStageErrors(std::vector<std::string> args) = 0;
    virtual void updateStage(std::vector<std::string> args) = 0;
    virtual std::string getStageName() = 0;
protected:
    bool stage_completed = false;
};