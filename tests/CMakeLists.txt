find_package(GTest CONFIG REQUIRED)

set(TEST_SOURCES "test.cpp")

add_executable("${APP_NAME}_tests" ${TEST_SOURCES})

target_link_libraries("${APP_NAME}_tests" PRIVATE utils)

target_link_libraries("${APP_NAME}_tests" PRIVATE GTest::gtest GTest::gtest_main)

add_test(Tests "${APP_NAME}_tests")
