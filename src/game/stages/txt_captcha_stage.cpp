#include "txt_captcha_stage.h"

bool TxtCaptchaStage::validateStage()
{
    return true;
}

std::map<std::string, std::vector<std::string>> TxtCaptchaStage::getStageErrors()
{
    return errors;
}

void TxtCaptchaStage::updateStage(std::string args)
{
    
}

std::string TxtCaptchaStage::getStageName()
{
    return "txtcaptcha";
}