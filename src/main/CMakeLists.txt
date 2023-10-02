set(source_list "main.cpp")

add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE ${source_list})
set_target_properties(${APP_NAME} PROPERTIES
            BUNDLE True
            MACOSX_BUNDLE_BUNDLE_NAME "Login Languish"
            # MACOSX_BUNDLE_ICON_FILE "0.1"
            # MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
            # MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
            # MACOSX_BUNDLE_LS_SYS_VERSION "10.13.4"
            )

target_link_libraries(${APP_NAME} PRIVATE utils game)

if (PLATFORM MATCHES "MAC")
    target_link_libraries(${APP_NAME}
        PUBLIC
        "-framework WebKit"
    )
elseif (PLATFORM MATCHES "WIN")
    find_package(unofficial-webview2 CONFIG REQUIRED)
    target_link_libraries(${APP_NAME} PRIVATE unofficial::webview2::webview2)
endif()

find_path(ZSERGE_WEBVIEW_INCLUDE_DIRS "webview.h")
target_include_directories(${APP_NAME} PUBLIC ${ZSERGE_WEBVIEW_INCLUDE_DIRS})

find_package(RapidJSON CONFIG REQUIRED)
target_link_libraries(${APP_NAME} PRIVATE rapidjson)