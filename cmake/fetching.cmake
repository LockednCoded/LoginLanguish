if (NOT EXISTS ${CMAKE_SOURCE_DIR}/vcpkg)
	execute_process(
		COMMAND git clone https://github.com/microsoft/vcpkg
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}	
	)
	if (PLATFORM MATCHES "WIN")
		execute_process(
			COMMAND ./vcpkg/bootstrap-vcpkg.bat
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/vcpkg
		)
	else()
		execute_process(
			COMMAND ./bootstrap-vcpkg.sh
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/vcpkg
		)
	endif()
endif()



# if (NOT EXISTS ${CMAKE_SOURCE_DIR}/libs/webview/webview.h)
#     make_directory(libs/webview)
# 		file(DOWNLOAD https://raw.githubusercontent.com/webview/webview/master/webview.h ${CMAKE_SOURCE_DIR}/libs/webview/webview.h SHOW_PROGRESS)
# 		file(DOWNLOAD https://raw.githubusercontent.com/webview/webview/master/webview.cc ${CMAKE_SOURCE_DIR}/libs/webview/webview.cc SHOW_PROGRESS)
# endif()

# if (PLATFORM MATCHES "WIN")
#     set(WEBVIEW2_NUPKG_FILENAME ${CMAKE_SOURCE_DIR}/libs/webview2/webview2.nupkg)
#     if (NOT EXISTS ${WEBVIEW2_NUPKG_FILENAME})
#         make_directory(libs/webview2)
# 				file(DOWNLOAD https://www.nuget.org/api/v2/package/Microsoft.Web.WebView2/ ${WEBVIEW2_NUPKG_FILENAME} SHOW_PROGRESS)
# 				execute_process(
# 						COMMAND ${CMAKE_COMMAND} -E tar xzf ${WEBVIEW2_NUPKG_FILENAME}
# 						WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/libs/webview2
# 				)
				
#     endif()
# endif()


# # include(FetchContent)

# # FetchContent_Declare(
# #   googletest
# #   URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
# # )
# # # For Windows: Prevent overriding the parent project's compiler/linker settings
# # set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# # FetchContent_MakeAvailable(googletest)

# set(GOOGLE_TESTS_ZIP_FILENAME ${CMAKE_SOURCE_DIR}/libs/googletest/googletest.zip)
# if (NOT EXISTS ${GOOGLE_TESTS_ZIP_FILENAME}) 
# 		make_directory(libs/googletest)
# 		file(DOWNLOAD https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip ${GOOGLE_TESTS_ZIP_FILENAME} SHOW_PROGRESS)
# 		execute_process(
# 				COMMAND ${CMAKE_COMMAND} -E tar xzf ${GOOGLE_TESTS_ZIP_FILENAME}
# 				WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/libs/googletest
# 		)
# endif()