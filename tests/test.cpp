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
    std::string resourcesPath = getResourcesPath();
    std::cout << "Resources path: " << resourcesPath << std::endl;
    // expect resourcesPath to end with "bin"
    // this is because the test is put directory. 
    // on macOS, in the bundled executable, the resourcesPath will end with "AppName.app/Contents/Resources".
    std::size_t pos = std::string(resourcesPath).find_last_of(getSeparator());
    std::string actual = resourcesPath.substr(pos + 1);
    std::string expected = "bin";
    EXPECT_EQ(resourcesPath.substr(resourcesPath.size() - expected.size()), expected);
}