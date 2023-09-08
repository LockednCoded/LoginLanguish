set(source_list "password_validator.cpp"
                "password_validator.h"
)

add_library(game STATIC ${source_list})

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})