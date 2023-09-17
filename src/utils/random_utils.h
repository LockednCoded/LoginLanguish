#pragma once

#include <vector>

namespace rand_utils {
    int randomInt(int min, int max);
    
    template <typename T> void shuffle(std::vector<T> &vector) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(vector.begin(), vector.end(), gen);
    }
}