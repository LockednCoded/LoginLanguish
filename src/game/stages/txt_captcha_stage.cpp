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
TxtCaptchaStage::TxtCaptchaStage(GameManager *gameManager) : Stage(gameManager)
{
    name = "txtcaptcha";
    field_errors = {
        {"txtcaptcha", std::vector<std::string>()}};

    setNewChallenge();
}

bool TxtCaptchaStage::setNewChallenge()
{
    if (challenges_remaining.size() == 0)
    {
        captcha_passed = true;
        challenge_text = "";
        image_url = "";
        current_challenge = -1;
        return false;
    }
    else if (challenges_remaining.size() == 3)
    {
        current_challenge = 0;
    }
    else
    {
        /* Set the current challenge to a random one of the remaining challenges*/
        std::set<char>::iterator it = challenges_remaining.begin();
        std::advance(it, rand() % challenges_remaining.size());
        current_challenge = *it;
    }
    challenges_remaining.erase(current_challenge);
    current_roll_identifier = "";
    last_round_error = "";

    rerollChallenge();

    return true;
}

void TxtCaptchaStage::rerollChallenge()
{
    switch (current_challenge)
    {
    case MENACING_CAPTCHAS:
    {
        challenge_text = "Please type the text you see above";
        std::string dir = "datasets/menacing";
        fs::path imagePath;
        do
        {
            imagePath = file_utils::getRandomFile(file_utils::getPathToResource(dir));
            image_url = file_utils::convertPathToFrontendString(imagePath);
        } while (image_url.compare(current_roll_identifier) == 0);
        current_roll_identifier = image_url;
        challenge_answer = imagePath.stem().u8string();
        std::replace(challenge_answer.begin(), challenge_answer.end(), '_', ' ');
        break;
    }

    default:
        std::cout << "Invalid challenge type: " << current_challenge << std::endl;
        throw std::invalid_argument("Invalid challenge type");
        break;
    }
}

void TxtCaptchaStage::progressStage()
{
    if (txt_captcha.compare(challenge_answer) == 0)
    {
        setNewChallenge();
    }
    else
    {
        last_round_error = "Incorrect answer. Please try again.";
        rerollChallenge();
    }
}

/*!
    @brief validates the stage
    @details validates the stage by checking if the requirements are met
    @return true if the stage is valid, false otherwise
*/
bool TxtCaptchaStage::validateStage()
{
    return captcha_passed;
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

    updateErrors(field);
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

    fieldStates.AddMember("captchaPassed", captcha_passed, allocator);

    rapidjson::Value challengeTextValue(challenge_text.c_str(), allocator);
    fieldStates.AddMember("challengeText", challengeTextValue, allocator);

    rapidjson::Value errorValue(last_round_error.c_str(), allocator);
    fieldStates.AddMember("lastRoundError", errorValue, allocator);

    return fieldStates;
};