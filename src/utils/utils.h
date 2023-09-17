/*!
    @file utils.h
    @brief handles generic tasks
    @author Jeb Nicholson
    @copyright 2023 Locked & Coded
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "rapidjson/document.h"

/*!
 @brief loads content from specified file to a string
 @param path to file
 @return file content
*/
std::string loadStringFromFile(std::string filepath);

std::string JSEncode(const std::string &message);
std::string JSEncode(const std::vector<std::string> &message);
std::string JSONToString(const rapidjson::Document &doc);
std::string url_encode(const std::string &value);
std::string base64Decode(const std::string &value);