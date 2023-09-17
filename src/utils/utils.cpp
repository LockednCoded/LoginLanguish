/*!
	@file utils.cpp
	@brief string load utility
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
#include <curl/curl.h>

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

std::string url_encode(const std::string &value)
{
	CURL *curl = curl_easy_init();
	return curl_easy_escape(curl, value.c_str(), value.length());
}
std::string url_decode(const std::string &value)
{
	CURL *curl = curl_easy_init();
	return curl_easy_unescape(curl, value.c_str(), value.length(), NULL);
}

std::string base64Decode(const std::string &value)
{
	return base64_decode(value);
}