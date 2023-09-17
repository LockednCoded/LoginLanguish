#pragma once

#include <vector>
#include <string>

namespace file_utils
{
    std::vector<std::string> listSubdirectories(std::string path);
    std::vector<std::string> listFiles(std::string path);
    std::vector<std::string> getNRandomFilesFromSubdirectories(int n, std::vector<std::string> directories);
    std::vector<std::string> getNRandomFiles(int n, std::string directory);
}