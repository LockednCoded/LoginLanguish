#include <gtest/gtest.h>
#include "random_utils.h"

int reps = 1000; // number of repetitions for each test

// test cases for randomInt function
TEST(RandUtilsTest, RandomInt) {
    int min = 0;
    int max = 100;

    for (int i = 0; i < 1000; i++) {
        int randNum = rand_utils::randomInt(min, max);
        ASSERT_GE(randNum, min); // check random int is greater than or equal to min
        ASSERT_LE(randNum, max); // check random int is less than or equal to max
    }
}

// test cases for randomSizeT function with bounds
TEST(RandUtilsTest, RandomSizeTWithBounds) {
    size_t min = 10;
    size_t max = 50;

    for (int i = 0; i < 1000; i++) {
        size_t randSize = rand_utils::randomSizeT(min, max);
        ASSERT_GE(randSize, min); // check random size_t is greater than or equal to min
        ASSERT_LE(randSize, max); // check random size_t is less than or equal to max
    }
}

// test cases for randomSizeT function without bounds
TEST(RandUtilsTest, RandomSizeTNoBounds) {
    size_t max = 100;

    for (int i = 0; i < reps; i++) {
        size_t randSize = rand_utils::randomSizeT(max);
        ASSERT_GE(randSize, 0);    // check random size_t is greater than or equal to 0
        ASSERT_LE(randSize, max);  // check random size_t is less than or equal to max
    }
}