/*!
    @file credentials_stage.cpp
    @brief the CredentialsStage class is the class that represents the credentials stage of the game
    @author Jack Searle, Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#pragma once

#include "../game_manager.h"
#include "name_stage.h"
#include "stage.h"
#include <vector>

/*!
    @brief the CredetialsStage class is a class that represents the credentials stage in the game
    @details contains concrete stage implementions for the credentials stage in the game
*/
class CredentialsStage : public Stage {
public:
    CredentialsStage(GameManager *gameManager);

    bool validateStage();
    void update(const rapidjson::Value &req);
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);

    // username error messages
    std::string lengthError = "Username must be between 8 and 24 characters in length.";
    std::string invalidCharError = "Invalid characters in username.";
    std::string takenError = "Username is already taken.";
    // password error messages
    std::string tooShortError = "Password must be 8 or more characters."; // "Minimum password length not yet reached"?
    std::string missingDigitError = "Password must include atleast one digit (0-9).";
    std::string missingUppercaseError = "Password must include atleast one uppercase character (A-Z).";
    std::string missingLowercaseError = "Password must include atleast one lowercase character (a-z).";
    std::string missingSpecialError = "Password must include atleast one special character.";
    std::string missingPrimeError = "Password must include atleast one prime number.";
    std::string missingInitialsError = "Password must include your initials.";
    std::string missingColourError = "Password must include a colour.";
    std::string missingRomanNumError = "Pasword must include atleast one Roman numeral.";
    std::string notPalindromeError = "Password must be a palindrome.";
    std::string tooLongError = "Password must be 20 or less characters."; // "Maximum password length exceeded"?

private:
    void updateErrors(const std::string &field);
    std::string username = "";
    std::string password = "";
};