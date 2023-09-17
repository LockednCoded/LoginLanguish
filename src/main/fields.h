/*!
    @file fields.h
    @brief the Fields class is the class that manages the field states of the game
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#pragma once

#include <string>
#include "rapidjson/document.h"
#include <string>

class Fields
{
public:
	rapidjson::Document d;
	Fields();
	std::string updateFieldState(std::string args);
	std::string getFieldStates();
private:
	std::string getJSONString();
};