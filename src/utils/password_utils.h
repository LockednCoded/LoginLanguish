/*!
	@file password_utils.h
	@brief handles password verification tasks
	@author Jack Searle
	@copyright 2023 Locked & Coded
*/

#pragma once

#include <string>
#include <vector>
#include <algorithm>

namespace password_utils {
    bool isPalindrome(std::string input);
    bool isPrime(int n);
    bool hasPrime(std::string input);
    bool hasColour(std::string input);
}