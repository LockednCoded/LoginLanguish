/*!
    @file test.cpp
    @brief general tests
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#include <string>
#include <stdio.h>
#include <gtest/gtest.h>
#include "compatibility_utils.h"

// demonstrate some basic assertions.
TEST(Tests, FindResourcesPath) {
  std::string resourcesPath = compatibility_utils::getResourcesPath();
  std::cout << "Resources path: " << resourcesPath << std::endl;
  //Expect resourcesPath to end with "bin". This is because the test is put directory. On macOS, in the bundled executable, the resourcesPath will end with "AppName.app/Contents/Resources".
	std::size_t pos = std::string(resourcesPath).find_last_of(compatibility_utils::getSeparator());
  std::string actual = resourcesPath.substr(pos + 1);
  std::string expected = "bin";
  EXPECT_EQ(resourcesPath.substr(resourcesPath.size() - expected.size()), expected);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}