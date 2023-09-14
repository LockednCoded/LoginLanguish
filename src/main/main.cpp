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
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
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
  w.set_size(WINDOW_WIDTH, WINDOW_HEIGHT, WEBVIEW_HINT_FIXED);
  w.navigate("file://" + resourcesPath + "/index.html");

  w.bind("documentLoadCallback", onDocumentLoadCallback, &w);

  Fields *fields = new Fields();
  GameManager *gameManager = new GameManager();

  w.bind("cpp_setFieldState", [fields](std::string req) -> std::string
         {
  // Todo: parse field updates
    std::vector<std::string> args = parseArgs(req);
    // Log args
    std::cout << "cpp_setFieldState args: ";
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
    return ""; });

  w.bind("cpp_getGameState", [gameManager](std::string req) -> std::string
         {
          rapidjson::Document document = gameManager->getGameState();
          rapidjson::StringBuffer buffer;
          rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
          document.Accept(writer);
          std::string result = buffer.GetString();
          std::cout << "cpp_getGameState result: " << result << std::endl;
          std::string dummy = R"""(
            {
            "stage": 1,
            "stages": [
              {
                "name": "name",
                "state": {
                  "firstName": {
                    "value": "Joe",
                    "errors": "",
                    "disabled": false
                  },
                  "lastName": {
                    "value": "Biden",
                    "errors": "",
                    "disabled": false
                  }
                }
              },
              {
                "name": "credentials",
                "state": {
                  "username": {
                    "value": "",
                    "errors": "",
                    "disabled": false
                  },
                  "password": {
                    "value": "",
                    "errors": "",
                    "disabled": false
                  }
                }
              },
              {
                "name": "extras",
                "state": {
                  "dob": {
                    "value": "",
                    "errors": "",
                    "disabled": false
                  },
                  "tsAndCs": {
                    "value": "false",
                    "errors": "",
                    "disabled": false
                  }
                }
              },
              {
                "name": "txtcaptcha",
                "state": {
                  "txtcaptcha": {
                    "value": "",
                    "errors": "",
                    "disabled": false
                  }
                }
              }
            ]
          }
          )""";
          return JSEncode(dummy); });
  w.bind("cpp_setNextStage", [gameManager](std::string req) -> std::string
         {
    // Todo: deal with progressing stage
    std::cout << "cpp_setNextStage req: " << req << std::endl; 
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
