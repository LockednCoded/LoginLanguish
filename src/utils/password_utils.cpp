/*!
	@file password_utils.cpp
	@brief handles password verification tasks
	@author Jack Searle
	@copyright 2023 Locked & Coded
*/

#include <string>
#include <vector>
#include "string_utils.h"

namespace password_utils {
    /*!
        @brief checks if a string is a palindrome
        @details iterates through the first half of the string and checks 
        it is being mirrored in the other half
        @param input the string to be checked
        @return true if the string is a palindrome, otherwise false
    */
    bool isPalindrome(std::string input){
        // find midpoint of the password
        int midpoint = input.length() / 2;
        
        // check if the first half is the same as the second half reversed
        for (int i = 0; i < midpoint; i++) {
            if (input[i] != input[input.length() - i - 1]) {
                return false;
            }
        }
        return true;
    }

    /*!
        @brief checks if a number is prime
        @details checks base cases before iterating through all integers up to
        the square root of the number being checked.
        @param n the integer to be checked
        @return true if n is a prime number, otherwise false
    */
    bool isPrime(int n){
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;

        for (int i = 5; i*i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }

    /*!
        @brief checks if a string contains a prime number
        @details checks through strings for entire numbers (15 will be read as 15, not 1 and 5)
        before checking if any of those numbers are prime.
        @param input the string to be checked for prime numbers
        @return true if the string contains a prime number, otherwise false
    */
    bool hasPrime(std::string input){
        std::vector<int> numbers;
        std::string numStr;
        // iterate through string and append any number to nums
        for (int i = 0; i < input.length(); i++){
            if (isdigit(input[i]))
                numStr += input[i];
            if (numStr.length() > 0 && (!isdigit(input[i]) || i == input.length()-1)){
                numbers.push_back(std::stoi(numStr));
                numStr = "";
            }
        }
        // iterate through numbers and check if they are prime
        for (int num : numbers){
            if (isPrime(num))
                return true;
        }
        return false;
    }

    /*!
        @brief checks if a string contains a colour
        @details iterates through list of colours and checks whether a lowercase copy 
        of the input string contains the colour.
        @param input the string to be checked for colours
        @return true if the string contains a colour, otherwise false
    */
    bool hasColour(std::string input){
        // vector of all accepted colours
        std::vector<std::string> colours = {
            "red", "orange", "yellow", "green", "blue", "indigo", "violet",
            "black", "white", "gray", "grey", "pink", "brown", "purple",
            "cyan", "magenta", "lime", "olive", "maroon", "navy", "teal",
            "lavender", "turquoise", "gold", "silver", "bronze", "beige",
            "salmon", "coral", "orchid", "peru", "khaki", "crimson",
            "chartreuse", "aqua", "plum", "sienna", "turquoise", "almond",
            "slate", "sepia", "azure", "ivory", "tan", "sapphire", "ruby",
            "stone", "jade", "peach", "mauve", "indigo", "mahogany",
            "lilac", "rose", "wine", "snow", "smoke", "egg", "bronze",
            "fuchsia", "apricot", "ash", "azure", "blush", "burgundy", 
            "camel", "charcoal", "chestnut", "chocolate", "copper", "cream",
            "desert", "ebony", "grape", "lemon", "maroon", "moss", 
            "mustard", "onyx", "crayola", "pantone", "bud", "pine", "puce",
            "berry", "rust", "sand", "shell", "sky", "vanilla", "tuscan"
        };
        // convert input to lowercase
        input = string_utils::toLowerCase(input);
        // iterate through colours and check if they are in the string
        for (std::string colour : colours){
            if (input.find(colour) != std::string::npos)
                return true;
        }
        return false;
    }

}