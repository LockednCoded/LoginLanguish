#include <string>
#include <vector>

class GameManager
{
public:
    std::string submitStage(std::string args);
    // std::string getStage();
    std::string getNextStage();
private:
    int current_stage = 0;
    std::vector<std::string> stages = {"name", "credentials", "details", "txtcaptcha"};
};