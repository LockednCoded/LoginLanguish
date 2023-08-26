/*!
 @file
 @brief string load utility
 @author Jeb Nicholson
 @copyright 2023 Locked & Coded
*/

#include "utils.h"

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