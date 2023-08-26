/*!
 @file utils.h
 @brief string load utility header file
 @author Jeb Nicholson
 @copyright 2023 Locked & Coded
*/

#include <iostream>
#include <fstream>

/*!
 @brief loads content from specified file to a string
 @param path to file
 @return file content
*/
std::string loadStringFromFile(std::string filepath);