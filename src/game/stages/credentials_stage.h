/*!
 @file credentials_stage.cpp
 @brief credentials stage validation
 @author Jack Searle
 @copyright 2023 Locked & Coded
*/

#pragma once

#include "../game_manager.h"
#include "name_stage.h"
#include "stage.h"
#include <vector>


class CredentialsStage : public Stage {
public:
    CredentialsStage(GameManager *gameManager);

    bool validateStage();
    std::vector<std::string> getStageErrors(std::vector<std::string> args);
    void update(const rapidjson::Value &req);
    std::string getStageName();
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);

    std::string tooShortError = "Password must include 8 or more characters."; // "Minimum password length not yet reached"?
    std::string missingDigitError = "Password must include atleast one digit (0-9).";
    std::string missingUppercaseError = "Password must include atleast one uppercase character (A-Z).";
    std::string missingLowercaseError = "Password must include atleast one lowercase character (a-z).";
    std::string missingSpecialError = "Password must include atleast one special character.";
    std::string missingPrimeError = "Password must include atleast one prime number.";
    std::string missingInitialsError = "Password must include your initials.";
    std::string missingColourError = "Password must include a colour.";
    std::string missingRomanNumError = "Pasword must include atleast one Roman numeral.";
    std::string notPalindromeError = "Password must be a palindrome.";
    std::string tooLongError = "Password must be 12 or less characters."; // "Maximum password length exceeded"?

protected:
    std::string name = "credentials";

private:
    GameManager* gm;
    NameStage* nameStage;
    std::string username = "";
    std::string password = "";
};