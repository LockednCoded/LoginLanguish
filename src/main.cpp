#include "main.h"

std::string resourcesPath;

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
  w.bind("documentLoadCallback", onDocumentLoadCallback, &w); 
  w.run();
  return 0;
}

void onDocumentLoadCallback(const std::string /*&seq*/, const std::string &req, void * arg) {
  webview::webview &w = *static_cast<webview::webview *>(arg);

  std::cout << "Received json message from JS: " << req << std::endl;
  if (!__DEBUG__) {
    w.eval("window.addEventListener('contextmenu', (event) => event.preventDefault());"); // Prevents use of the context menu
  }
}