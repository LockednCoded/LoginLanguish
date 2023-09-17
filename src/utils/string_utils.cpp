#include "string_utils.h"

namespace string_utils {
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