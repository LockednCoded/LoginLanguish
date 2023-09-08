/*!
 @file main.cpp
 @brief runs app
 @author Jeb Nicholson
 @copyright 2023 Locked & Coded

 @mainpage Login Languish
 Here is an overview of the main files:
 - @ref main.cpp "Loads html and runs webview app"
 - @ref utils.cpp "Utilities"
 - @ref compatibility_utils.cpp "Compatibility utilities"
*/

#include "webview.h"
#include <fstream>
#include <string>
#include <iostream>
#include "compatibility_utils.h"
#include "main.h"

std::string resourcesPath;

/*!
 @brief runs the webview
 @details runs the webview and calls a helper function to load html
 @return 0 if successful, 1 if failed.
*/
#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
#else
int main()
{
#endif

  resourcesPath = getResourcesPath();
  std::cout << "Resources path: " << resourcesPath << std::endl;

  webview::webview w(__DEBUG__, nullptr);

  if (__DEBUG__) {
    std::cout << "We're in debug mode" << std::endl;
  } else {
    std::cout << "We're in release mode" << std::endl;
  }

  w.set_title("Login Languish");
  w.set_size(WINDOW_WIDTH, WINDOW_HEIGHT, WEBVIEW_HINT_FIXED);
  w.navigate("file://" + resourcesPath + "/index.html");
  w.bind("testFunction", onDocumentLoadCallback, &w); 
  w.run();
  return 0;
}

/*!
 @brief loads html
 @details 
*/
void onDocumentLoadCallback(const std::string /*&seq*/, const std::string &req, void * arg) {
  webview::webview &w = *static_cast<webview::webview *>(arg);

  std::cout << "Received message from JS: " << req << std::endl;
  w.eval("document.getElementById('title').innerHTML = 'Hello from C++';");
  if (!__DEBUG__) {
    w.eval("window.addEventListener('contextmenu', (event) => event.preventDefault());"); // Prevents use of the context menu
  }
  std::string js = loadStringFromFile(resourcesPath + "/assets/index.js");
  std::cout << "JS: " << js << std::endl;
  w.eval(js);
  std::string css = loadStringFromFile(resourcesPath + "/assets/index.css");
  std::cout << "CSS: " << css << std::endl;
  w.eval("var style = document.createElement('style'); style.innerHTML = `" + css + "`; document.head.appendChild(style);");

}