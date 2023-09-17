/*!
	@file utils.cpp
	@brief handles generic tasks
	@author Jeb Nicholson
	@copyright 2023 Locked & Coded
*/

#include "utils.h"
#include "cpp-base64/base64.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>

/*!
 @brief loads content from specified file to a string
 @param path to file
 @return file content
*/
std::string loadStringFromFile(std::string filepath)
{
	std::cout << "Loading file: " << filepath << std::endl;
	std::ifstream ifs(filepath);
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	if (ifs.fail())
	{
		std::cout << "Error: File not found" << std::endl;
		throw std::runtime_error("File not found");
	}
	return content;
}

std::string JSEncode(const std::string &message)
{
	return "\"" + base64_encode(message) + "\"";
	// return "";
}

std::string JSEncode(const std::vector<std::string> &message)
{
	std::string result = "[";
	for (auto it = message.begin(); it != message.end(); ++it)
	{
		result += "\"" + base64_encode(*it) + "\"";
		if (it != message.end() - 1)
		{
			result += ",";
		}
	}
	result += "]";
	return result;
}
std::string JSONToString(const rapidjson::Document &doc)
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	std::string result = buffer.GetString();
	return result;
}

/**
 * From https://stackoverflow.com/a/17708801 (xperroni)
 */
std::string url_encode(const std::string &value)
{
	std::ostringstream escaped;
	escaped.fill('0');
	escaped << std::hex;

	for (std::string::const_iterator i = value.begin(), n = value.end(); i != n; ++i)
	{
		std::string::value_type c = (*i);

		// Keep alphanumeric and other accepted characters intact
		if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
		{
			escaped << c;
			continue;
		}

		// Any other characters are percent-encoded
		escaped << std::uppercase;
		escaped << '%' << std::setw(2) << int((unsigned char)c);
		escaped << std::nouppercase;
	}

	return escaped.str();
}