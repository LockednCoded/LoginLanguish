/*
* @file main.h
* @brief main header file
* @author Jeb Nicholson
* @copyright 2023 Locked & Coded
*/

#include "webview.h"
#include <fstream>
#include <string>
#include <iostream>

#include "compatibility_utils.h"
#include "utils.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 672

#ifdef __DEBUG__
#define __DEBUG__ 1
#else
#define __DEBUG__ 0
#endif

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/);
#else
int main();
#endif

void onDocumentLoadCallback(const std::string /*&seq*/, const std::string &req, void * /*arg*/);