/*!
 @file
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
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

std::string getResourcesPath();

char getSeparator();