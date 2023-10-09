set(source_list "game_manager.cpp"
                "game_manager.h"
                "stages/stage.h"
                "stages/stage.cpp"
                "stages/credentials_stage.cpp"
                "stages/credentials_stage.h"
                "stages/name_stage.cpp"
                "stages/name_stage.h"
                "stages/txt_captcha_stage.cpp"
                "stages/txt_captcha_stage.h"
                "stages/extras_stage.cpp"
                "stages/extras_stage.h"
                "stages/image_captcha_stage.cpp"
                "stages/image_captcha_stage.h"
                "stages/dwayne_stage.cpp"
                "stages/dwayne_stage.h"
                "stages/end_stage.cpp"
                "stages/end_stage.h"
)

add_library(game STATIC ${source_list})

target_link_libraries(game PRIVATE utils)

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(RapidJSON CONFIG REQUIRED)
target_link_libraries(game PRIVATE rapidjson)
