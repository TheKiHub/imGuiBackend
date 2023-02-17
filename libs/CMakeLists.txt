#-------------------------------------------------------------------------------------------------------
# Lib creation
#-------------------------------------------------------------------------------------------------------
message(DEBUG "Creating ${PROJECT_NAME}")

add_library(${PROJECT_NAME}
            src/imGuiCustom.cpp
            src/openglTextureStorage.cpp
        )

# define relocatable include files for target
target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )

# add alias for easier use
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# enable all compiler specific warnings for the target
set_target_warnings(${PROJECT_NAME})

#-------------------------------------------------------------------------------------------------------
# Dependency handling
#-------------------------------------------------------------------------------------------------------
handleExternals(NAME imGui)
handleExternals(NAME opengl)
handleExternals(NAME stbImage)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
            imGui
            stbImage
        PRIVATE
            ${OPENGL_LIBRARIES}
        )

if(WITH_PIPELINE_GENERATOR)
    target_link_libraries(${PROJECT_NAME} PUBLIC pipelineGenerator)
endif ()

#-------------------------------------------------------------------------------------------------------
# Installation
#-------------------------------------------------------------------------------------------------------
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/fonts ${CMAKE_BINARY_DIR}/app/fonts)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/fonts DESTINATION bin)

string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

packageProject(
        NAME ${PROJECT_NAME}
        VERSION ${PROJECT_VERSION}
        NAMESPACE ${PROJECT_NAME}
        BINARY_DIR ${PROJECT_BINARY_DIR}
        INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include/
        INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
        VERSION_HEADER "${VERSION_HEADER_LOCATION}"
        COMPATIBILITY SameMajorVersion
        DEPENDENCIES "imGui; OpenGL; stbImage"
)
