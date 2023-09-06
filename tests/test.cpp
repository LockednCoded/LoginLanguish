#include <string>
#include <stdio.h>
#include <gtest/gtest.h>
#include "compatibility_utils.h"

// Demonstrate some basic assertions.
TEST(Tests, FindResourcesPath) {
  std::string resourcesPath = getResourcesPath();
  std::cout << "Resources path: " << resourcesPath << std::endl;
  //Expect resourcesPath to end with "build". This is because the test is run from the build directory. On macOS, in the bundled executable, the resourcesPath will end with "AppName.app/Contents/Resources".
  std::string expected = "Debug";
  EXPECT_EQ(resourcesPath.substr(resourcesPath.size() - expected.size()), expected);
}