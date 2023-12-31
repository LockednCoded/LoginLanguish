/*!
	@file random_utils.h
	@brief handles pseudo-random tasks
	@author Cameron Bruce
	@copyright 2023 Locked & Coded
*/

#pragma once

#include <vector>
#include <random>

namespace rand_utils {
    int randomInt(int min, int max);

    size_t randomSizeT(size_t min, size_t max);
    size_t randomSizeT(size_t max);

    template <typename T> void shuffle(std::vector<T> &vector) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(vector.begin(), vector.end(), gen);
    }
}