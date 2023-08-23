if (NOT EXISTS ${CMAKE_SOURCE_DIR}/libs/webview/webview.h)
    make_directory(libs/webview)
		file(DOWNLOAD https://raw.githubusercontent.com/webview/webview/master/webview.h ${CMAKE_SOURCE_DIR}/libs/webview/webview.h SHOW_PROGRESS)
		file(DOWNLOAD https://raw.githubusercontent.com/webview/webview/master/webview.cc ${CMAKE_SOURCE_DIR}/libs/webview/webview.cc SHOW_PROGRESS)
endif()

if (PLATFORM MATCHES "WIN")
    set(WEBVIEW2_NUPKG_FILENAME ${CMAKE_SOURCE_DIR}/libs/webview2/webview2.nupkg)
    if (NOT EXISTS ${WEBVIEW2_NUPKG_FILENAME})
        make_directory(libs/webview2)
				file(DOWNLOAD https://www.nuget.org/api/v2/package/Microsoft.Web.WebView2/ ${WEBVIEW2_NUPKG_FILENAME} SHOW_PROGRESS)
				execute_process(
						COMMAND ${CMAKE_COMMAND} -E tar xzf ${WEBVIEW2_NUPKG_FILENAME}
						WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/libs/webview2
				)
				
    endif()
endif()