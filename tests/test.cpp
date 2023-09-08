#include <string>
#include <stdio.h>
#include <gtest/gtest.h>
#include "compatibility_utils.h"

// Demonstrate some basic assertions.
TEST(Tests, FindResourcesPath) {
    std::string resourcesPath = getResourcesPath();
  std::cout << "Resources path: " << resourcesPath << std::endl;
  //Expect resourcesPath to end with "bin". This is because the test is put directory. On macOS, in the bundled executable, the resourcesPath will end with "AppName.app/Contents/Resources".
	std::size_t pos = std::string(resourcesPath).find_last_of(getSeparator());
  std::string actual = resourcesPath.substr(pos + 1);
  std::string expected = "bin";
  EXPECT_EQ(resourcesPath.substr(resourcesPath.size() - expected.size()), expected);
}