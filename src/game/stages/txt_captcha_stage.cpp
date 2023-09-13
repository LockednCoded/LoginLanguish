#include "txt_captcha_stage.h"

bool TxtCaptchaStage::validateStage()
{
    return true;
}

std::string TxtCaptchaStage::getStageErrors(std::vector<std::string> args)
{
    return "";
}

void TxtCaptchaStage::updateStage(std::vector<std::string> args)
{
    
}

std::string TxtCaptchaStage::getStageName()
{
    return "txtcaptcha";
}