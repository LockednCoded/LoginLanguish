#pragma once

#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace file_utils
{
    std::vector<fs::path> listSubdirectories(fs::path path);
    std::vector<fs::path> listFiles(fs::path path);
    std::vector<fs::path> getNRandomFilesFromSubdirectories(size_t n, std::vector<fs::path> directories);
    std::vector<fs::path> getNRandomFiles(size_t n, fs::path directory);
    fs::path getRandomFile(fs::path directory);
    fs::path getPathToResource(std::string resource);
    std::vector<std::string> convertPathsToStrings(std::vector<fs::path> paths);
}