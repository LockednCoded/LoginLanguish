#include <vector>
#include <map>
#include <string>

class Stage
{
public:
    virtual bool validateStage() = 0;
    virtual std::map<std::string, std::vector<std::string>> getStageErrors() = 0;
    virtual void updateStage(std::string args) = 0;
    virtual std::string getStageName() = 0;
protected:
    bool stage_completed = false;
    std::map<std::string, std::vector<std::string>> errors;
};