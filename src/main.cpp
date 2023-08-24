/*
* @file main.cpp
* @brief runs app
* @author Jeb Nicholson
* @copyright 2023 Locked & Coded
*/

#include "webview.h"
#include <fstream>
#include <string>
#include <iostream>
#include "compatibility_utils.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 672

/*
* @brief runs the webview
* @details locates the html file to be displayed and runs the webview using it.
* @return 0 if successful, 1 if failed.
*/
#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
                   LPSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
#else
int main()
{
#endif
  std::string resourcesPath = getResourcesPath();
  std::cout << "Resources path: " << resourcesPath << std::endl;
  std::ifstream ifs(resourcesPath + "/assets/test.html");
  std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
  if (ifs.fail())
  {
    std::cout << "Error: File not found" << std::endl;
    return 1;
  }
  webview::webview w(true, nullptr);
  w.set_title("Basic Example");
  w.set_size(WINDOW_WIDTH, WINDOW_HEIGHT, WEBVIEW_HINT_FIXED);
  w.set_html(content);
  w.run();
  return 0;
}
