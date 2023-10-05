/*!
	@file string_utils.cpp
	@brief handles string-related tasks
	@author Cameron Bruce, Jack Searle
	@copyright 2023 Locked & Coded
*/

#include "string_utils.h"

namespace string_utils {
    /*!
        @brief title case string converter
        @details converts any string to title case (capitalised first letter)
        @param str string to be converted
        @return the converted title case string
    */
    std::string toTitleCase(std::string str) {
        if (str.length() == 0) {
            return str;
        }

        str[0] = toupper(str[0]);

        for (int i = 1; i < str.length(); i++) {
            if (str[i - 1] == ' ') {
                str[i] = toupper(str[i]);
            }
        }

        return str;
    }

    /*!
        @brief lowercase string converter
        @details converts any string to lowercase
        @param str string to be converted
        @return the converted lowercase string
    */
    std::string toLowerCase(std::string str){
        if (str.length() == 0){
            return str;
        }
        for (int i = 0; i < str.length(); i++){
            str[i] = tolower(str[i]);
        }
        return str;
    }
}