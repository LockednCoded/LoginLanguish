set(source_list "main.cpp")

add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE ${source_list})

target_link_libraries(${APP_NAME} PRIVATE utils)

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