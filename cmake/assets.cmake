if (PLATFORM MATCHES "MAC")
    set(ASSETS_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/../Resources/") 
elseif (PLATFORM MATCHES "WIN")
    set(ASSETS_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/") 
endif()

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