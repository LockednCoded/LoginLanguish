/*!
    @file image_captcha_stage.cpp
    @brief the implementation of the ImageCaptchaStage class
    @author Cameron Brue
    @copyright 2023 Locked & Coded
*/

#include <filesystem>
#include <algorithm>
#include <random>
#include <iterator>
#include <iostream>

#include "compatibility_utils.h"
#include "image_captcha_stage.h"

namespace fs = std::filesystem;

/*!
    @brief constructor for ImageCaptchaStage
    @param gameManager the game manager object owning this stage
*/
ImageCaptchaStage::ImageCaptchaStage(GameManager *gameManager){
    name = "imagecaptcha";
    gm = gameManager;
;
    std::string path = getResourcesPath() +   "/datasets/celeb-faces/";
    std::vector<std::string> celebrities = listSubdirectories(path);


    int random_celeb = randomInt(0, celebrities.size() - 1);
    std::string selected_celebrity = celebrities[random_celeb];
    celebrities.erase(celebrities.begin() + random_celeb);

    int num_celebrity_images = listFiles(selected_celebrity).size();
    int num_correct = std::min(randomInt(3, 5), num_celebrity_images);
    
    std::vector<std::string> selected_celebrity_files = getNRandomFiles(num_correct, selected_celebrity);
    std::vector<std::string> incorrect_celebrity_files = getNRandomFilesFromSubdirectories(9 - num_correct, celebrities);

    std::vector<std::string> all_files;
    all_files.insert(all_files.end(), selected_celebrity_files.begin(), selected_celebrity_files.end());
    all_files.insert(all_files.end(), incorrect_celebrity_files.begin(), incorrect_celebrity_files.end());

    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(all_files), std::end(all_files), rng);
    
    image_urls = all_files;
    correct_images = selected_celebrity_files;
    std::string celebrity_name = selected_celebrity.substr(selected_celebrity.find_last_of("/\\") + 1);
    std::replace(celebrity_name.begin(), celebrity_name.end(), '_', ' ');

    //convery celebrity name to title case
    celebrity_name[0] = toupper(celebrity_name[0]);
    for (int i = 1; i < celebrity_name.size(); i++) {
        if (celebrity_name[i - 1] == ' ') {
            celebrity_name[i] = toupper(celebrity_name[i]);
        }
    }
    challenge_text = "Select all images of " + celebrity_name + ".";
};

/*!
    @brief validates the stage
    @details validates the stage by checking if the requirements are met
    @return true if the stage is valid, false otherwise
*/
bool ImageCaptchaStage::validateStage()
{
    return true;
}

/*!
    @brief updates the stage
    @details updates the stage by updating the field values
    @param req the request object containing the field to update and the new value
*/
void ImageCaptchaStage::updateErrors(std::string field)
{   
    //TODO: implement this?
}

/*!
    @brief updates the stage
    @details updates the stage by updating the field values
    @param req the request object containing the field to update and the new value
*/
void ImageCaptchaStage::update(const rapidjson::Value &req)
{
    std::string field = req[REQ_FIELD_INDEX].GetString();
    if (field.compare("selected") == 0) {
        const rapidjson::Value& valueArray = req[REQ_VALUE_INDEX].GetArray();
        std::vector<int> new_selection;
        for (int i = 0; i < (int) valueArray.Size(); i++) {
            new_selection.push_back(valueArray[i].GetInt());
        }
        selected = new_selection;
    }
    updateErrors(field);
}

/*!
    @brief gets the field states
    @details gets the field states by returning a rapidjson object containing the field states
    @param allocator the rapidjson allocator
    @return the rapidjson object containing the field states
*/
rapidjson::Value ImageCaptchaStage::getFieldStates(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value fieldStates(rapidjson::kObjectType);

    rapidjson::Value imagesValue(rapidjson::kArrayType);
    for (std::string image : image_urls) {
        rapidjson::Value imageValue(image.c_str(), allocator);
        imagesValue.PushBack(imageValue, allocator);
    }
    fieldStates.AddMember("images", imagesValue, allocator);

    rapidjson::Value challengeTextValue(challenge_text.c_str(), allocator);
    fieldStates.AddMember("challengeText", challengeTextValue, allocator);

    rapidjson::Value selectedValue(rapidjson::kArrayType);
    for (int i : selected) {
        rapidjson::Value intValue(i);
        selectedValue.PushBack(intValue, allocator);
    }
    fieldStates.AddMember("selected", selectedValue, allocator);

    return fieldStates;
};

std::vector<std::string> ImageCaptchaStage::listSubdirectories(std::string path) {
    std::vector<std::string> subdirectories;
    
    for (const auto & entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            subdirectories.push_back(entry.path().string());
        }
    }

    return subdirectories;
}

std::vector<std::string> ImageCaptchaStage::listFiles(std::string path) {
    std::vector<std::string> files;
    
    for (const auto & entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().string());
        }
    }

    return files;
}

int ImageCaptchaStage::randomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

std::vector<std::string> ImageCaptchaStage::getNRandomFiles(int n, std::string directory) 
{
    std::vector<std::string> files = listFiles(directory);
    std::vector<std::string> random_files;

    for (int i = 0; i < n; i++) {
        int random_index = randomInt(0, files.size() - 1);
        random_files.push_back(files[random_index]);
        files.erase(files.begin() + random_index);
    }

    return random_files;
}

std::vector<std::string> ImageCaptchaStage::getNRandomFilesFromSubdirectories(
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
        int random_subdirectory = randomInt(0, directories_available.size() - 1);

        std::vector<std::string> files = files_map[directories_available[random_subdirectory]];

        if (files.size() == 0) {
            directories_available.erase(directories_available.begin() + random_subdirectory);
            i--;
            continue;
        }

        int random_file = randomInt(0, files.size() - 1);
        random_files.push_back(files[random_file]);
        files.erase(files.begin() + random_file);
    }

    return random_files;
}
