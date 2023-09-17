/*!
    @file compatibility_utils.h
    @brief handles platform compatibility
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

namespace compatibility_utils {
    std::string getResourcesPath();
    char getSeparator();
}