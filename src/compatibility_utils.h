/*!
 @file compatibility_utils.h
 @brief platform compatibility header file
 @author Jeb Nicholson
 @copyright 2023 Locked & Coded
*/

#pragma once

#include <string>
#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif
#ifdef _WIN32
//#include <libloaderapi.h>
#include <windows.h>
#endif

std::string getResourcesPath();