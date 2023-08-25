cmake_minimum_required(VERSION 3.5)

include(cmake/fetching.cmake)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

project(LoginLanguish)

set(APP_NAME "LoginLanguish")
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_compile_options(-Wall)

if (true)
    add_compile_definitions(__DEBUG__)
endif ()

if (APPLE)
    set(PLATFORM MAC)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(PLATFORM WIN)
endif()



file(GLOB source_list src/*.cpp)
list(FILTER source_list EXCLUDE REGEX ".*main.cpp$") # exclude main.cpp from library (it's in the executable)

add_library("${APP_NAME}_lib" STATIC ${source_list})



if (PLATFORM MATCHES "MAC")
    target_link_libraries("${APP_NAME}_lib"
        PUBLIC
        "-framework CoreFoundation"
        "-framework WebKit"
    )
elseif (PLATFORM MATCHES "WIN")
    find_package(unofficial-webview2 CONFIG REQUIRED)
    target_link_libraries("${APP_NAME}_lib" PRIVATE unofficial::webview2::webview2)
endif()

find_path(ZSERGE_WEBVIEW_INCLUDE_DIRS "webview.h")
target_include_directories("${APP_NAME}_lib" PUBLIC ${ZSERGE_WEBVIEW_INCLUDE_DIRS})


include(cmake/assets.cmake)

file(GLOB test_list src/test/*.cpp)

add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE)
target_link_libraries(${APP_NAME} PRIVATE "${APP_NAME}_lib")
target_sources(${APP_NAME} PRIVATE src/main.cpp)

add_executable(
    tests
    ${test_list}
)
target_link_libraries(tests PRIVATE "${APP_NAME}_lib")

enable_testing()
    
find_package(GTest CONFIG REQUIRED)
target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(Tests tests)
