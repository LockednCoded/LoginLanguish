#include "stage.h"

class TxtCaptchaStage : public Stage {
public:
    bool validateStage();
    std::map<std::string, std::vector<std::string>> getStageErrors();
    void updateStage(std::string args);
    std::string getStageName();
private:
    std::string username;
    std::string password;
};