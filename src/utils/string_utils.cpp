/*!
	@file string_utils.cpp
	@brief handles string-related tasks
	@author Cameron Bruce
	@copyright 2023 Locked & Coded
*/

#include "string_utils.h"

namespace string_utils {
    /*!
        @brief title case string converter
        @details converts any string to title case (capitalised first letter)
        @param str string to be converted
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
}