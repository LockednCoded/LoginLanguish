find_package(GTest CONFIG REQUIRED)

set(TEST_SOURCES    "test.cpp"
                    "password_validator_test.cpp")

add_executable("${APP_NAME}_tests" ${TEST_SOURCES})

target_link_libraries("${APP_NAME}_tests" PRIVATE utils game)

target_link_libraries("${APP_NAME}_tests" PRIVATE GTest::gtest GTest::gtest_main)

include(GoogleTest)

gtest_discover_tests("${APP_NAME}_tests")
