cmake_minimum_required(VERSION 3.5)

include(cmake/fetching.cmake)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

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

include(cmake/assets.cmake)


enable_testing()

add_subdirectory(src)
add_subdirectory(tests)