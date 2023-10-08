/*!
    @file image_captcha_stage.cpp
    @brief the implementation of the ImageCaptchaStage class
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#include <filesystem>
#include <algorithm>
#include <random>
#include <iterator>
#include <iostream>
#include <string>

#include "compatibility_utils.h"
#include "image_captcha_stage.h"
#include "string_utils.h"
#include "file_utils.h"
#include "random_utils.h"

const char *NUM_STRINGS[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

/*!
    @brief constructor for ImageCaptchaStage
    @param gameManager the game manager object owning this stage
*/
ImageCaptchaStage::ImageCaptchaStage(GameManager *gameManager) : Stage(gameManager)
{
    name = "imagecaptcha";

    setNewChallenge();
};

/*!
    @brief validates the stage
    @details validates the stage by checking if the requirements are met
    @return true if the stage is valid, false otherwise
*/
bool ImageCaptchaStage::validateStage()
{
    return challenges_remaining.size() == 0;
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
        std::vector<std::string> new_selection;
        for (rapidjson::SizeType i = 0; i < valueArray.Size(); i++) {
            new_selection.push_back(valueArray[i].GetString());
        }
        selected = new_selection;
    }
}

bool ImageCaptchaStage::setNewChallenge()
{
    correct_images.clear();
    image_urls.clear();
    image_labels.clear();
    if (challenges_remaining.size() == 0)
    {
        challenge_text = "";
        current_challenge = -1;
        return false;
    }
    else if (challenges_remaining.size() == 3)
    {
        current_challenge = 0;
    }
    else
    {
        /* Set the current challenge to a random one of the remaining challenges*/
        std::set<char>::iterator it = challenges_remaining.begin();
        std::advance(it, rand() % challenges_remaining.size());
        current_challenge = *it;
    }
    challenges_remaining.erase(current_challenge);
    last_round_error = "";

    initialiseChallenge();

    return true;
}

void ImageCaptchaStage::progressStage()
{
    last_round_error = "";
    bool stagePassed = true;

    if (selected.size() == correct_images.size()) {
        for (std::string image : selected) {
            if (std::find(correct_images.begin(), correct_images.end(), image) == correct_images.end()) {
                last_round_error = "Incorrect selection.";
                stagePassed = false;
                break;
            }
        }
    } else {
        last_round_error = "Incorrect selection.";
        stagePassed = false;
    }

    selected.clear();
    if (stagePassed)
    {
        if (!setNewChallenge())
        {
            gm->getNextStage();
            return;
        }
    }
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

    rapidjson::Value imageLabelsValue(rapidjson::kArrayType);
    for (std::string image_label : image_labels)
    {
        rapidjson::Value imageLabelValue(image_label.c_str(), allocator);
        imageLabelsValue.PushBack(imageLabelValue, allocator);
    }
    fieldStates.AddMember("imageLabels", imageLabelsValue, allocator);

    rapidjson::Value challengeTextValue(challenge_text.c_str(), allocator);
    fieldStates.AddMember("challengeText", challengeTextValue, allocator);

    rapidjson::Value selectedValue(rapidjson::kArrayType);
    for (std::string str : selected) {
        rapidjson::Value strValue(str.c_str(), allocator);
        selectedValue.PushBack(strValue, allocator);
    }
    fieldStates.AddMember("selected", selectedValue, allocator);

    rapidjson::Value errorValue(last_round_error.c_str(), allocator);
    fieldStates.AddMember("lastRoundError", errorValue, allocator);

    return fieldStates;
};

/*!
    @brief initialises the captcha images
    @details initialises the captcha images by selecting a random correct directory and selecting a random number of images from that directory
    @details the remaining images are selected from the other directories
    @param dataset_path the path to the dataset
*/
void ImageCaptchaStage::initialiseDatasetImages(fs::path dataset_path, size_t MAX_NUM_IMAGES, size_t MAX_NUM_CORRECT, size_t MIN_NUM_CORRECT)
{
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
    std::string dir_name = selected_dir.filename().u8string(); //get the name of the directory
    std::replace(dir_name.begin(), dir_name.end(), '_', ' '); //replace underscores with spaces
    dir_name = string_utils::toTitleCase(dir_name); //convert to title case
    challenge_text = "Select all images of " + dir_name + ".";
}
void ImageCaptchaStage::initialiseChallenge()
{
    const size_t MAX_NUM_IMAGES = 9;
    const size_t MAX_NUM_CORRECT = 5;
    const size_t MIN_NUM_CORRECT = 3;
    switch (current_challenge)
    {
    case FREEDOM_CAPTCHAS:
    {
        int num_correct = rand_utils::randomInt(MIN_NUM_CORRECT, MAX_NUM_CORRECT);
        initialiseCountryImages(num_correct, MAX_NUM_IMAGES);
        break;
    }
    case CELEB_CAPTCHAS:
    case MUFFIN_DOG_CAPTCHAS:
    {
        fs::path dataset_path;
        dataset_path = file_utils::getPathToResource(current_challenge == CELEB_CAPTCHAS ? "datasets/celeb-faces" : "datasets/dogs-muffins");
        initialiseDatasetImages(dataset_path, MAX_NUM_IMAGES, MAX_NUM_CORRECT, MIN_NUM_CORRECT);
        break;
    }
    default:
        std::cout << "Invalid challenge type: " << current_challenge << std::endl;
        throw std::invalid_argument("Invalid challenge type");
        break;
    }
}

void ImageCaptchaStage::initialiseCountryImages(size_t num_correct, size_t total_num)
{
    std::vector<std::vector<std::string>> countriesData = file_utils::readCSV(file_utils::getPathToResource("datasets/countries/_country_data.csv"));
    int choice = rand_utils::randomInt(0, 1); // 0= Authoritarian, 1= Democratic
    std::string filter;
    std::string antiFilter;
    std::string num_correct_string = NUM_STRINGS[num_correct];
    switch (choice)
    {
    case 0: // Authoritarian
        challenge_text = num_correct > 1 ? ("Select all " + num_correct_string + " authoritarian regimes.") : "Select the authoritarian regime.";
        filter = "Authoritarian";
        antiFilter = "Full democracy";
        break;
    case 1: // Democratic
        challenge_text = num_correct > 1 ? ("Select all " + num_correct_string + " democracies.") : "Select the democracy.";
        filter = "Full democracy";
        antiFilter = "Authoritarian";
        break;
    }
    rand_utils::shuffle(countriesData);
    size_t num_correct_needed = num_correct;
    size_t num_incorrect_needed = total_num - num_correct_needed;
    std::vector<std::vector<std::string>> countriesChosen;
    for (std::vector<std::string> country : countriesData)
    {
        if (num_correct_needed == 0 && num_incorrect_needed == 0)
            break;
        std::string countryPath = file_utils::convertPathToFrontendString(file_utils::getPathToResource("datasets/countries/images/" + country[0] + ".png"));
        std::vector<std::string> countryPair = {country[0], countryPath};
        if (country[2].compare(filter) == 0)
        {
            if (num_correct_needed > 0)
            {
                correct_images.push_back(countryPath);
                countriesChosen.push_back(countryPair);
                num_correct_needed--;
            }
        }
        else if (country[2].compare(antiFilter) == 0)
        {
            if (num_incorrect_needed > 0)
            {
                countriesChosen.push_back(countryPair);
                num_incorrect_needed--;
            }
        }
    }
    rand_utils::shuffle(countriesChosen);
    for (std::vector<std::string> country : countriesChosen)
    {
        image_urls.push_back(country[1]);
        image_labels.push_back(country[0]);
    }
}