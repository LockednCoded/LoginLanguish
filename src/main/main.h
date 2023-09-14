/*!
 @file main.h
 @brief main header file
 @author Jeb Nicholson
 @copyright 2023 Locked & Coded
*/

#pragma once

#include <fstream>
#include <string>
#include <iostream>


#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 672

#ifdef __DEBUG__
#define __DEBUG__ 1
#else
#define __DEBUG__ 0
#endif

/*!
 @brief runs the webview
 @details runs the webview and calls a helper function to load html
 @return 0 if successful, 1 if failed.
*/
#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/);
#else
int main();
#endif

/*!
 @brief loads html
 @details 
*/
void onDocumentLoadCallback(const std::string /*&seq*/, const std::string &req, void * /*arg*/);

std::string JSEncode(const std::string& message);
std::string JSEncode(const std::vector<std::string> &message);