project(LoginLanguish)
cmake_minimum_required(VERSION 3.3.2)

include(cmake/App.cmake)

set(SOURCES "src/Game.h"
            "src/Game.cpp"
            "src/main.cpp")

add_app("${SOURCES}")