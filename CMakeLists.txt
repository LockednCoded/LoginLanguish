cmake_minimum_required(VERSION 3.5)
project(LoginLanguish)
set(APP_NAME "LoginLanguish")
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)
file(GLOB source_list src/*.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (APPLE)
    set(PLATFORM MAC)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(PLATFORM WIN)
endif()

include(cmake/fetching.cmake)

add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE ${source_list})
add_library(webview STATIC libs/webview/webview.cc)

if (PLATFORM MATCHES "MAC")
    set(ASSETS_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/../Resources/assets") 

    target_link_libraries(${APP_NAME}
        PRIVATE
        "-framework CoreFoundation"
        "-framework WebKit"
    )
elseif (PLATFORM MATCHES "WIN")
    set(ASSETS_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/assets") 

    target_include_directories(webview PUBLIC libs/webview2/build/native/include)
endif()


target_include_directories(webview PUBLIC libs/webview)
target_link_libraries(${APP_NAME}
    PRIVATE
    webview
)


add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR}
    ${ASSETS_PATH}
    COMMENT "Copying assets to ${ASSETS_PATH}"
)