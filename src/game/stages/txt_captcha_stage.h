#pragma once

#include "stage.h"

class TxtCaptchaStage : public Stage {
public:
    bool validateStage();
    std::string getStageErrors(std::vector<std::string> args);
    void updateStage(std::vector<std::string> args);
    std::string getStageName();
private:
    std::string username;
    std::string password;
};