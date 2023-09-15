set(source_list "game_manager.cpp"
                "game_manager.h"
                "stages/stage.h"
                "stages/stage.cpp"
                "stages/credentials_stage.cpp"
                "stages/credentials_stage.h"
                "stages/details_stage.cpp"
                "stages/details_stage.h"
                "stages/name_stage.cpp"
                "stages/name_stage.h"
                "stages/txt_captcha_stage.cpp"
                "stages/txt_captcha_stage.h"
)

add_library(game STATIC ${source_list})

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(RapidJSON CONFIG REQUIRED)
target_link_libraries(game PRIVATE rapidjson)
