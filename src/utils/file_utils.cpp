#include "file_utils.h"
#include "random_utils.h"
#include "compatibility_utils.h"

#include <map>

namespace file_utils {
    std::vector<fs::path> listSubdirectories(fs::path path) {
        std::vector<fs::path> subdirectories;
        
        for (const auto & entry : fs::directory_iterator(path)) {
            if (entry.is_directory()) {
                subdirectories.push_back(entry.path());
            }
        }

        return subdirectories;
    }


    std::vector<fs::path> listFiles(fs::path path) {
        std::vector<fs::path> files;
        
        for (const auto & entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                files.push_back(entry.path());
            }
        }

        return files;
    }

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

    fs::path getRandomFile(fs::path directory) {
        std::vector<fs::path> files = listFiles(directory);
        size_t random_index = rand_utils::randomSizeT(files.size() - 1);
        return files[random_index];
    }


    std::vector<fs::path> getNRandomFilesFromSubdirectories(
        size_t n, 
        std::vector<fs::path> directories)
    {
        std::map<fs::path, std::vector<fs::path>> files_map;
        for (auto directory : directories) {
            files_map[directory] = listFiles(directory);
        }

        std::vector<fs::path> directories_available = directories;
        std::vector<fs::path> random_files;

        for (size_t i = 0; i < n; i++) {
            size_t random_subdirectory = rand_utils::randomSizeT(directories_available.size() - 1);

            std::vector<fs::path> files = files_map[directories_available[random_subdirectory]];

            if (files.size() <= 0) {
                directories_available.erase(directories_available.begin() + random_subdirectory);
                i--;
                continue;
            }

            size_t random_file = rand_utils::randomSizeT(files.size() - 1);
            random_files.push_back(files[random_file]);
            files.erase(files.begin() + random_file);
        }

        return random_files;
    }

    fs::path getPathToResource(std::string resource) {
        fs::path resources_path = compatibility_utils::getResourcesPath();
        resources_path = resources_path / resource;
        return resources_path.make_preferred();
    }

    std::vector<std::string> convertPathsToFrontendStrings(std::vector<fs::path> paths) {
        std::vector<std::string> strings;

        for (fs::path path : paths) {
            strings.push_back(convertPathToFrontendString(path));
        }
        return strings;
    }

    std::string convertPathToFrontendString(fs::path path) {
        fs::path base = compatibility_utils::getResourcesPath();
        fs::path relative = fs::relative(path, base);
        std::string string = relative.u8string();
        std::replace(string.begin(), string.end(), '\\', '/');
        return string;
    }

}
