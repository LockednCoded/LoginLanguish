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
	@param path string representation of file path
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

/*!
	@brief encodes a string in base 64
	@param message string to be encoded
	@return the encoded base 64 string
*/
std::string JSEncode(const std::string &message)
{
	return "\"" + base64_encode(message) + "\"";
	// return "";
}

/*!
	@brief encodes strings in a vector to base 64
	@param message vector of strings to be encoded
	@return string representation of an array of base 64 encoded messages
*/
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

/*!
	@brief converts RapidJSON documents to a string representation
	@param doc the RapidJSON document to be converted
	@return string representation JSON
*/
std::string JSONToString(const rapidjson::Document &doc)
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	std::string result = buffer.GetString();
	return result;
}

/*!
	@brief decodes a base 64 message
	@param value message to be decoded
	@return the decoded message
*/
std::string base64Decode(const std::string &value)
{
	return base64_decode(value);
}

bool caseInsensitiveEquals(const std::string &a, const std::string &b)
{
	return std::equal(a.begin(), a.end(), b.begin(), b.end(), [](char a, char b)
										{ return tolower(a) == tolower(b); });
}

/*!
	@brief encodes a string into a url
	@details from https://stackoverflow.com/a/17708801 (xperroni)
	@param value the string to be encoded
	@return string representation of the encoded url
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