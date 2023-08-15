project(LoginLanguish)
cmake_minimum_required(VERSION 3.3.2)

add_custom_target(npm-target COMMAND cd ${CMAKE_SOURCE_DIR}/static_site && npm run install_and_build)

include(cmake/App.cmake)

set(SOURCES "src/Game.h"
            "src/Game.cpp"
            "src/main.cpp")

add_app("${SOURCES}")
