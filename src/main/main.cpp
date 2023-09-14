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

#include <fstream>
#include <string>
#include <iostream>
#include "webview.h"
#include "compatibility_utils.h"
#include "utils.h"
#include "main.h"
#include "fields.h"
#include "game_manager.h"
#include "cpp-base64/base64.h"
#include "parse_args.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

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

  if (__DEBUG__)
  {
    std::cout << "We're in debug mode" << std::endl;
  }
  else
  {
    std::cout << "We're in release mode" << std::endl;
  }

  w.set_title("Login Languish");
  w.set_size(WINDOW_WIDTH, WINDOW_HEIGHT, WEBVIEW_HINT_FIXED);
  w.navigate("file://" + resourcesPath + "/index.html");

  w.bind("documentLoadCallback", onDocumentLoadCallback, &w);

  Fields *fields = new Fields();
  GameManager *gameManager = new GameManager();

  w.bind("cpp_updateFieldState", [fields](std::string req) -> std::string
         { return JSEncode(fields->updateFieldState(req)); });
  w.bind("cpp_getFieldStates", [fields](std::string req) -> std::string
         { return JSEncode(fields->getFieldStates()); });
  w.bind("cpp_getGameState", [gameManager](std::string req) -> std::string
         {
          rapidjson::Document document = gameManager->getGameState();
          rapidjson::StringBuffer buffer;
          rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
          document.Accept(writer);
          std::string result = buffer.GetString();
          std::cout << "cpp_getGameState result: " << result << std::endl;
          return JSEncode(result); });

  const std::vector<std::string> testArgs = {"test", "test2"};
  const std::string testArgsString = JSEncode(testArgs);
  std::cout << "testArgsString: " << testArgsString << std::endl;

  std::cout << "Starting webview" << std::endl;

  w.run();
  return 0;
}

/*!
 @brief loads html
 @details
*/
void onDocumentLoadCallback(const std::string /*&seq*/, const std::string &req, void *arg)
{
  webview::webview &w = *static_cast<webview::webview *>(arg);

  std::cout << "Received message from JS: " << req << std::endl;
  w.eval("console.log('Hello from C++! :)');");
  if (!__DEBUG__)
  {
    w.eval("window.addEventListener('contextmenu', (event) => event.preventDefault());"); // Prevents use of the context menu
  }
}

std::string JSEncode(const std::string &message)
{
  return "\"" + base64_encode(message) + "\"";
  // return "";
}

std::string JSEncode(const std::vector<std::string> &message)
{
  std::string result = "[";
  for (auto it = message.begin(); it != message.end(); ++it)
  {
    result += "\"" + base64_encode(*it) + "\"";
    if (it != message.end() - 1)
    {
      result += ",";
    }
  }
  result += "]";
  return result;
}