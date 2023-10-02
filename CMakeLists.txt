cmake_minimum_required(VERSION 3.6)

include(cmake/fetching.cmake)
set(TESTING ON CACHE BOOL "Enable testing")

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

include(cmake/configuration.cmake)

project(LoginLanguish)

set(APP_NAME "LoginLanguish")
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_compile_options(-Wall)

# if CMAKE_BUILD_TYPE is Debug, add __DEBUG__ to compile definitions
if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(__DEBUG__)
    add_compile_definitions(__CHEAT_MODE__)
endif ()

if (APPLE)
    set(PLATFORM MAC)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(PLATFORM WIN)
endif()

include(cmake/assets.cmake)
add_subdirectory(src)

if (TESTING)
    enable_testing()

    add_subdirectory(tests)
endif()