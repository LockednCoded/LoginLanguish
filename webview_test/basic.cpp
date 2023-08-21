#include "webview.h"
#include <fstream>
#include <string>
#include <iostream>

#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 672

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
                   LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
#else
int main() {
#endif
  std::ifstream ifs("test.html");
  std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
  // std::cout << content << std::endl;
  webview::webview w(true, nullptr);
  w.set_title("Basic Example");
  w.set_size(WINDOW_WIDTH, WINDOW_HEIGHT, WEBVIEW_HINT_FIXED);
  w.set_html(content);
  w.run();
  return 0;
}
