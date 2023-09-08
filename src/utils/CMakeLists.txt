set(source_list "compatibility_utils.cpp"
                "compatibility_utils.h"
                "utils.cpp"
                "utils.h"
)

add_library(utils STATIC ${source_list})

if (PLATFORM MATCHES "MAC")
    target_link_libraries(utils
        PUBLIC
        "-framework CoreFoundation"
    )
endif()

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})