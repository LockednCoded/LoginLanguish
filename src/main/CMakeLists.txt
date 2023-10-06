set(source_list "main.cpp")

add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE ${source_list})

target_link_libraries(${APP_NAME} PRIVATE utils game)

if (PLATFORM MATCHES "MAC")
    target_link_libraries(${APP_NAME}
        PUBLIC
        "-framework WebKit"
    )
    set_target_properties(${APP_NAME} PROPERTIES
            BUNDLE True
            MACOSX_BUNDLE_BUNDLE_NAME "Login Languish"
            MACOSX_BUNDLE_ICON_FILE "LoginLanguish" 
            )
elseif (PLATFORM MATCHES "WIN")
    find_package(unofficial-webview2 CONFIG REQUIRED)
    target_link_libraries(${APP_NAME} PRIVATE unofficial::webview2::webview2)
endif()


# And this part tells CMake where to find and install the file itself

find_path(ZSERGE_WEBVIEW_INCLUDE_DIRS "webview.h")
target_include_directories(${APP_NAME} PUBLIC ${ZSERGE_WEBVIEW_INCLUDE_DIRS})

find_package(RapidJSON CONFIG REQUIRED)
target_link_libraries(${APP_NAME} PRIVATE rapidjson)