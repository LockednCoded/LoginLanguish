find_package(GTest CONFIG REQUIRED)

set(TEST_SOURCES    "test.cpp"
                    "credentials_stage_test.cpp"
                    "extras_stage_test.cpp"
                    "image_captcha_stage_test.cpp"
                    "name_stage_test.cpp"
                    "txt_captcha_stage_test.cpp")

add_executable("${APP_NAME}_tests" ${TEST_SOURCES})

target_link_libraries("${APP_NAME}_tests" PRIVATE utils game)

target_link_libraries("${APP_NAME}_tests" PRIVATE GTest::gtest GTest::gtest_main)

find_package(RapidJSON CONFIG REQUIRED)
target_link_libraries("${APP_NAME}_tests" PRIVATE rapidjson)

include(GoogleTest)

gtest_discover_tests("${APP_NAME}_tests")
