#pragma once

#include <vector>
#include <string>

namespace file_utils
{
    std::vector<std::string> listSubdirectories(std::string path);
    std::vector<std::string> listFiles(std::string path);
    std::vector<std::string> getNRandomFilesFromSubdirectories(size_t n, std::vector<std::string> directories);
    std::vector<std::string> getNRandomFiles(size_t n, std::string directory);
}