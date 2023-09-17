/*!
    @file txt_captcha_stage.cpp
    @brief the implementation of the TxtCaptchaStage class
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#include "txt_captcha_stage.h"
#include <filesystem>
#include "compatibility_utils.h"
#include <iostream>
#include "utils.h"
#include "file_utils.h"

/*!
    @brief constructor for TxtCaptchaStage
    @param gameManager the game manager object owning this stage
*/
TxtCaptchaStage::TxtCaptchaStage(GameManager *gameManager)
{
    name = "txtcaptcha";
    gm = gameManager;
    field_errors = {
        {"txtcaptcha", std::vector<std::string>()}};

    setNewChallenge();
}

bool TxtCaptchaStage::setNewChallenge()
{
    if (challenges_remaining.size() == 0)
        return false;
    char x;
    if (challenges_remaining.size() == 3)
    {
        x = 0;
    }
    else
    {
        std::set<char>::iterator it = challenges_remaining.begin();
        std::advance(it, rand() % challenges_remaining.size());
        x = *it;
    }
    challenges_remaining.erase(x);

    switch (x)
    {
    case 0: // Menacing captchas
    {
        challenge_text = "Please type the text you see above";
        std::string dir = "datasets/menacing";
        fs::path imagePath = file_utils::getRandomFile(file_utils::getPathToResource(dir));
        image_url = file_utils::convertPathToFrontendString(imagePath);
        challenge_answer = imagePath.stem().u8string();
        std::replace(challenge_answer.begin(), challenge_answer.end(), '_', ' '); 
        break;
    }

    default:
        challenge_text = "Validated.";
        image_url = "";
        break;
    }
    return true;
}

/*!
    @brief validates the stage
    @details validates the stage by checking if the requirements are met
    @return true if the stage is valid, false otherwise
*/
bool TxtCaptchaStage::validateStage()
{
    return true;
}

/*!
    @brief updates the stage
    @details updates the stage by updating the field values
    @param req the request object containing the field to update and the new value
*/
void TxtCaptchaStage::updateErrors(std::string field)
{
    if (field.compare("txtcaptcha") == 0)
    {
        if (txt_captcha.compare("") == 0)
            return;
        std::vector<std::string> errors;
        if (txt_captcha.compare(challenge_answer) != 0)
            errors.push_back("Incorrect answer");
        field_errors["txtcaptcha"] = errors;
    }
}

/*!
    @brief updates the stage
    @details updates the stage by updating the field values
    @param req the rapidjson request object containing the field to update and the new value
*/
void TxtCaptchaStage::update(const rapidjson::Value &req)
{
    std::string field = req[REQ_FIELD_INDEX].GetString();

    if (field.compare("txtcaptcha") == 0)
        txt_captcha = req[REQ_VALUE_INDEX].GetString();
    if (txt_captcha.compare("") != 0 && txt_captcha.compare(challenge_answer) == 0)
    {
        txt_captcha = "";
        setNewChallenge();
    }

    updateErrors(field);
}

void TxtCaptchaStage::progressStage()
{
    
}

/*!
    @brief gets the field states
    @details gets the field states by returning a rapidjson object containing the field states
    @param allocator the rapidjson allocator
    @return the rapidjson value object containing the field states
*/
rapidjson::Value TxtCaptchaStage::getFieldStates(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value fieldStates(rapidjson::kObjectType);

    rapidjson::Value txtCaptchaValue(txt_captcha.c_str(), allocator);
    rapidjson::Value txtCaptchaObj = createFieldState("txtcaptcha", txtCaptchaValue, allocator);
    fieldStates.AddMember("txtcaptcha", txtCaptchaObj, allocator);

    rapidjson::Value imageUrlValue(image_url.c_str(), allocator);
    fieldStates.AddMember("imageURL", imageUrlValue, allocator);

    rapidjson::Value challengeTextValue(challenge_text.c_str(), allocator);
    fieldStates.AddMember("challengeText", challengeTextValue, allocator);

    return fieldStates;
};