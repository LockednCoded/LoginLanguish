#include "file_utils.h"
#include "random_utils.h"

#include <map>
#include <filesystem>

namespace fs = std::filesystem;

namespace file_utils {
    std::vector<std::string> listSubdirectories(std::string path) {
        std::vector<std::string> subdirectories;
        
        for (const auto & entry : fs::directory_iterator(path)) {
            if (entry.is_directory()) {
                subdirectories.push_back(entry.path().string());
            }
        }

        return subdirectories;
    }


    std::vector<std::string> listFiles(std::string path) {
        std::vector<std::string> files;
        
        for (const auto & entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                files.push_back(entry.path().string());
            }
        }

        return files;
    }

    std::vector<std::string> getNRandomFiles(int n, std::string directory) 
    {
        std::vector<std::string> files = listFiles(directory);
        std::vector<std::string> random_files;

        for (int i = 0; i < n; i++) {
            int random_index = rand_utils::randomInt(0, files.size() - 1);
            random_files.push_back(files[random_index]);
            files.erase(files.begin() + random_index);
        }

        return random_files;
    }


    std::vector<std::string> getNRandomFilesFromSubdirectories(
        int n, 
        std::vector<std::string> directories)
    {
        std::map<std::string, std::vector<std::string>> files_map;
        for (auto directory : directories) {
            files_map[directory] = listFiles(directory);
        }

        std::vector<std::string> directories_available = directories;
        std::vector<std::string> random_files;

        for (int i = 0; i < n; i++) {
            int random_subdirectory = rand_utils::randomInt(0, directories_available.size() - 1);

            std::vector<std::string> files = files_map[directories_available[random_subdirectory]];

            if (files.size() == 0) {
                directories_available.erase(directories_available.begin() + random_subdirectory);
                i--;
                continue;
            }

            int random_file = rand_utils::randomInt(0, files.size() - 1);
            random_files.push_back(files[random_file]);
            files.erase(files.begin() + random_file);
        }

        return random_files;
    }

}
