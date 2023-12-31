/*!
	@file random_utils.cpp
	@brief handles pseudo-random tasks
	@author Cameron Bruce
	@copyright 2023 Locked & Coded
*/

#include <random>

#include "random_utils.h"

namespace rand_utils {
    /*!
        @brief retrieves a pseudo-random integer
        @param min lower bound
        @param max upper bound
        @return the random integer
    */
    int randomInt(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(min, max);

        return dis(gen);
    }

    /*!
        @brief retrieves a pseudo-random size_t
        @param min lower bound
        @param max upper bound
        @return the random size_t
    */
    size_t randomSizeT(size_t min, size_t max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dis(min, max);

        return dis(gen);
    }

    /*!
        @brief retrieves a pseudo-random size_t
        @param max upper bound
        @return the random size_t
    */
    size_t randomSizeT(size_t max) {
        return randomSizeT(0, max);
    }
}