/*!
 @file main.cpp
 @brief runs app
 @author Jeb Nicholson
 @copyright 2023 Locked & Coded

 @mainpage Login Languish
 Here is an overview of the main files:
 - @ref main.cpp "runs app"
 - @ref utils.cpp "string load utility"
 - @ref compatibility_utils.cpp "platform compatibility"
 - @ref parse_args.cpp "argument parsing utility"
 - @ref fields.cpp "field state manager"
 - @ref game_manager.cpp "implementation of the GameManager class"
 - @ref stage.cpp "implementation of the Stage class"
 - @ref name_stage.cpp "implementation of the NameStage class"
 - @ref credentials_stage.cpp "implementation of the CredentialsStage class"
 - @ref extras_stage.cpp "implementation of the ExtrasStage class"
 - @ref text_captcha_stage.cpp "implementation of the TextCaptchaStage class"
 - @ref image_captcha_stage.cpp "implementation of the ImageCaptchaStage class"
*/

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "webview.h"
#include "compatibility_utils.h"
#include "utils.h"
#include "main.h"
#include "fields.h"
#include "game_manager.h"
#include "parse_args.h"

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
  if (__DEBUG__)
  {
    w.set_size(WINDOW_WIDTH, WINDOW_HEIGHT, WEBVIEW_HINT_NONE);
  }
  else
  {
    w.set_size(WINDOW_WIDTH, WINDOW_HEIGHT, WEBVIEW_HINT_FIXED);
  }
  w.navigate("file://" + resourcesPath + "/index.html");

  w.bind("documentLoadCallback", onDocumentLoadCallback, &w);

  Fields *fields = new Fields();
  GameManager *gameManager = new GameManager();

  w.bind("cpp_setFieldState", [fields, gameManager](std::string req) -> std::string
         {
    rapidjson::Document document;
    document.Parse(req.c_str());
    const rapidjson::Value &reqArray = document.GetArray();
    gameManager->updateField(reqArray);
    return ""; });

  w.bind("cpp_getGameState", [gameManager](std::string req) -> std::string
         {
          rapidjson::Document doc = gameManager->getGameState();
          const std::string gameStateString = JSONToString(doc);
          std::cout << "cpp_getGameState result: " << gameStateString << std::endl;
          return JSEncode(gameStateString); });
  w.bind("cpp_setNextStage", [gameManager](std::string req) -> std::string
         {
          std::cout << "Getting next stage" << std::endl;
          gameManager->getNextStage();
          return ""; });

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
