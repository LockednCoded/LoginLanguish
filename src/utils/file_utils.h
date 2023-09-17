/*!
	@file file_utils.h
	@brief handles file related tasks
	@author Cameron Bruce
	@copyright 2023 Locked & Coded
*/

#pragma once

#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace file_utils
{
    std::vector<fs::path> listSubdirectories(fs::path path);
    std::vector<fs::path> listFiles(fs::path path);
    std::vector<fs::path> getNRandomFilesFromSubdirectories(size_t n, const std::vector<fs::path> &directories);
    std::vector<fs::path> getNRandomFiles(size_t n, fs::path directory);
    fs::path getRandomFile(fs::path directory);
    fs::path getPathToResource(const std::string &resource);
    std::vector<std::string> convertPathsToFrontendStrings(const std::vector<fs::path> &paths);
    std::string convertPathToFrontendString(fs::path paths);
}