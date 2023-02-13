add_executable(guiBackendExample src/main.cpp )
target_link_libraries(guiBackendExample
            guiBackend
        )

# Add the test image to the output folder
file(COPY ${CMAKE_CURRENT_LIST_DIR}/testImage.jpg DESTINATION ${CMAKE_BINARY_DIR}/app/)
