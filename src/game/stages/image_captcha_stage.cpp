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
#include "string_utils.h"
#include "file_utils.h"
#include "random_utils.h"

/*!
    @brief constructor for ImageCaptchaStage
    @param gameManager the game manager object owning this stage
*/
ImageCaptchaStage::ImageCaptchaStage(GameManager *gameManager){
    name = "imagecaptcha";
    gm = gameManager;

    initialiseCaptchaImages(file_utils::getPathToResource("datasets/celeb-faces"));
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
    @brief updates error messages
    @details updates the error messages for the given field
    @param field the name of the field to update
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

/*!
    @brief initialises the captcha images
    @details initialises the captcha images by selecting a random correct directory and selecting a random number of images from that directory
    @details the remaining images are selected from the other directories
    @param dataset_path the path to the dataset
*/
void ImageCaptchaStage::initialiseCaptchaImages(fs::path dataset_path) {
    const size_t MAX_NUM_IMAGES = 9;
    const size_t MAX_NUM_CORRECT = 5;
    const size_t MIN_NUM_CORRECT = 3;

    //get all directories in path
    std::vector<fs::path> available_dirs =  file_utils::listSubdirectories(dataset_path);

    //select a directory at random and remove it from the list
    size_t random_index = rand_utils::randomSizeT(available_dirs.size() - 1);
    fs::path selected_dir = available_dirs[random_index];
    available_dirs.erase(available_dirs.begin() + random_index);

    //select a random number of images from the selected directory
    size_t selected_dir_size = file_utils::listFiles(selected_dir).size();
    size_t num_correct_images = std::min(rand_utils::randomSizeT(MIN_NUM_CORRECT, MAX_NUM_CORRECT), selected_dir_size);
    std::vector<fs::path> correct_image_paths = file_utils::getNRandomFiles(num_correct_images, selected_dir);

    correct_images = file_utils::convertPathsToFrontendStrings(correct_image_paths);
    image_urls = correct_images;

    //select the remaining images from the other directories
    std::vector<fs::path> incorrect_dir_files = file_utils::getNRandomFilesFromSubdirectories(MAX_NUM_IMAGES - num_correct_images, available_dirs);
    std::vector<std::string> incorrect_images = file_utils::convertPathsToFrontendStrings(incorrect_dir_files);
    image_urls.insert(image_urls.end(), incorrect_images.begin(), incorrect_images.end());

    //shuffle the images
    rand_utils::shuffle(image_urls);

    //create challenge string
    std::string dir_string = selected_dir.string();
    std::string dir_name = dir_string.substr(dir_string.find_last_of("/\\") + 1); //get the name of the directory
    std::replace(dir_name.begin(), dir_name.end(), '_', ' '); //replace underscores with spaces
    dir_name = string_utils::toTitleCase(dir_name); //convert to title case
    challenge_text = "Select all images of " + dir_name + ".";
}