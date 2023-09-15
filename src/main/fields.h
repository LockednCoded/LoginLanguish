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