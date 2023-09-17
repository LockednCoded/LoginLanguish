set(source_list "compatibility_utils.cpp"
                "compatibility_utils.h"
                "utils.cpp"
                "utils.h"
                "parse_args.h"
                "parse_args.cpp"
                "file_utils.h"
                "file_utils.cpp"
                "string_utils.h"
                "string_utils.cpp"
                "random_utils.h"
                "random_utils.cpp"
)

add_library(utils STATIC ${source_list})

if (PLATFORM MATCHES "MAC")
    target_link_libraries(utils
        PUBLIC
        "-framework CoreFoundation"
    )
endif()

find_package(CURL REQUIRED)
target_link_libraries(utils PRIVATE CURL::libcurl)

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(RapidJSON CONFIG REQUIRED)
target_link_libraries(utils PRIVATE rapidjson)

find_path(CPP_BASE64_INCLUDE_DIRS "cpp-base64/base64.cpp")

add_library(cpp-base64 STATIC "${CPP_BASE64_INCLUDE_DIRS}/cpp-base64/base64.cpp")
target_include_directories(cpp-base64 PUBLIC "${CPP_BASE64_INCLUDE_DIRS}/cpp-base64")
target_link_libraries(utils PRIVATE cpp-base64)