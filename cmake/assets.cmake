if (PLATFORM MATCHES "MAC")
    list(APPEND ASSETS_PATHES "$<TARGET_FILE_DIR:${APP_NAME}>/../Resources/")
    if (TESTING)
        list(APPEND ASSETS_PATHES "$<TARGET_FILE_DIR:${APP_NAME}>/../../..")
    endif()
endif()
if (PLATFORM MATCHES "WIN")
    list(APPEND ASSETS_PATHES "$<TARGET_FILE_DIR:${APP_NAME}>")
endif()

add_custom_target(generate_static_site
    COMMAND npm run install_and_build 
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/static_site"
    COMMENT "Building static site"
    VERBATIM
)

add_custom_target(copy_static_site ALL DEPENDS generate_static_site)
add_custom_target(copy_assets ALL)

foreach(ASSETS_PATH IN LISTS ASSETS_PATHES)

    add_custom_command(TARGET copy_static_site
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/static_site/dist
        ${ASSETS_PATH}
        COMMENT "Copying static site to ${ASSETS_PATH}"
        VERBATIM
    )

    add_custom_command(TARGET copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${ASSETS_PATH}
        COMMENT "Copying assets to ${ASSETS_PATH}"
        VERBATIM
    )

endforeach()
