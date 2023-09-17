/*!
	@file file_utils.cpp
	@brief handles file related tasks
	@author Cameron Bruce
	@copyright 2023 Locked & Coded
*/

#include "file_utils.h"
#include "random_utils.h"
#include "compatibility_utils.h"
#include "utils.h"
#include <iostream>

#include <map>

namespace file_utils {
    /*!
        @brief lists subdirectories in a directory
        @details creates and returns a filepath vector of the subdirectories in the directory
        @param path path of the directory to list subdirectories from
        @return
    */
    std::vector<fs::path> listSubdirectories(fs::path path) {
        std::vector<fs::path> subdirectories;
        
        for (const auto & entry : fs::directory_iterator(path)) {
            if (entry.is_directory()) {
                subdirectories.push_back(entry.path());
            }
        }

        return subdirectories;
    }

    /*!
        @brief lists files in a directory
        @details creates and returns a filepath vector of the files in directory
        @param path path of the directory to list files from
        @return vector of file paths
    */
    std::vector<fs::path> listFiles(fs::path path) {
        std::vector<fs::path> files;
        
        for (const auto & entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                files.push_back(entry.path());
            }
        }

        return files;
    }

    /*!
        @brief retrieves n random files
        @details creates and returns a filepath vector of n random files in the directory
        @param n number of random files to return
        @param directory path of the directory to retrieve files from
        @return vector of n random file paths
    */
    std::vector<fs::path> getNRandomFiles(size_t n, fs::path directory) 
    {
        std::vector<fs::path> files = listFiles(directory);
        std::vector<fs::path> random_files;

        for (size_t i = 0; i < n; i++) {
            size_t random_index = rand_utils::randomSizeT(files.size() - 1);
            random_files.push_back(files[random_index]);
            files.erase(files.begin() + random_index);
        }

        return random_files;
    }

    /*!
        @brief retrieves a random file
        @details returns the filepath of a random file in the directory
        @param path path of the directory to retrieve the file from
        @return a random file's path
    */
    fs::path getRandomFile(fs::path directory) {
        std::vector<fs::path> files = listFiles(directory);
        size_t random_index = rand_utils::randomSizeT(files.size() - 1);
        return files[random_index];
    }

    /*!
        @brief retrieves n random files from given subdirectories
        @details creates and returns a file path vector of n random files from the subdirectories
        @param n number of random files to return
        @param subdirectories vector of subdirectories to retrieve random files from
        @return vector of n random file paths
    */
    std::vector<fs::path> getNRandomFilesFromSubdirectories(
        size_t n, 
        const std::vector<fs::path> &directories)
    {
        std::map<fs::path, std::vector<fs::path>> files_map;
        for (auto directory : directories) {
            files_map[directory] = listFiles(directory);
        }

        std::vector<fs::path> directories_available = directories;
        std::vector<fs::path> random_files;

        for (size_t i = 0; i < n; i++) {
            size_t random_subdirectory = rand_utils::randomSizeT(directories_available.size() - 1);

            std::vector<fs::path> *files = &files_map[directories_available[random_subdirectory]];

            if (files->size() == 0) {
                directories_available.erase(directories_available.begin() + random_subdirectory);
                i--;
                continue;
            }

            size_t random_file = rand_utils::randomSizeT(files->size() - 1);
            random_files.push_back((*files)[random_file]);
            files->erase(files->begin() + random_file);
        }

        return random_files;
    }

    /*!
        @brief retrieves the resource path
        @param resource string representation of resource
        @return the resource path
    */
    fs::path getPathToResource(const std::string &resource) {
        fs::path resources_path = compatibility_utils::getResourcesPath();
        resources_path = resources_path / resource;
        return resources_path.make_preferred();
    }

    /*!
        @brief converts file paths to frontend strings
        @details passes file paths in a given vector to a helper function to convert into strings for the frontend
        @param paths vector of file paths
        @return vector of frontend strings
    */
    std::vector<std::string> convertPathsToFrontendStrings(const std::vector<fs::path> &paths) {
        std::vector<std::string> strings;

        for (fs::path path : paths) {
            strings.push_back(convertPathToFrontendString(path));
        }
        return strings;
    }

    /*!
        @brief converts file path to frontend string
        @details converts the file path to a string relative to the frontend and url encodes it
        @param path a file path
        @return a frontend string
    */
    std::string convertPathToFrontendString(fs::path path) {
        fs::path base = compatibility_utils::getResourcesPath();
        fs::path relative = fs::relative(path, base);
        std::string filenameSafe = url_encode(relative.filename().u8string());
        std::string string = relative.parent_path().u8string() + "/" + filenameSafe;
        std::replace(string.begin(), string.end(), '\\', '/');
        return string;
    }

}
