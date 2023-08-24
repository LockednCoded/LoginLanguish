cmake_minimum_required(VERSION 3.5)
project(LoginLanguish)
set(APP_NAME "LoginLanguish")
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)
file(GLOB source_list src/*.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall)

if (true)
    add_compile_definitions(__DEBUG__)
endif ()

if (APPLE)
    set(PLATFORM MAC)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(PLATFORM WIN)
endif()

include(cmake/fetching.cmake)

add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE ${source_list})
add_library(webview STATIC libs/webview/webview.cc)

if (PLATFORM MATCHES "MAC")
    set(ASSETS_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/../Resources/") 

    target_link_libraries(${APP_NAME}
        PRIVATE
        "-framework CoreFoundation"
        "-framework WebKit"
    )
elseif (PLATFORM MATCHES "WIN")
    set(ASSETS_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/") 

    target_include_directories(webview PUBLIC libs/webview2/build/native/include)
endif()


target_include_directories(webview PUBLIC libs/webview)
target_link_libraries(${APP_NAME}
    PRIVATE
    webview
)

add_custom_target(generate_static_site
    COMMAND npm run install_and_build 
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/static_site"
	COMMENT "Building static site"
    VERBATIM
)

add_custom_target(copy_static_site ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/static_site/dist
    ${ASSETS_PATH}
    COMMENT "Copying static site to ${ASSETS_PATH}"
    DEPENDS generate_static_site
    VERBATIM
)

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR}
    ${ASSETS_PATH}
    COMMENT "Copying assets to ${ASSETS_PATH}"
    VERBATIM
)
