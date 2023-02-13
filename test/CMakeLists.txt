project(guiBackendTests LANGUAGES CXX)

option(${PROJECT_NAME}_TEST_BENCHMARK "Enable the benchmark tests for ${PROJECT_NAME}" OFF)
option(${PROJECT_NAME}_TEST_UNIT_TESTS "Enable the unit tests for ${PROJECT_NAME}" ON)

if (${PROJECT_NAME}_TEST_BENCHMARK)
    add_executable(benchmarkOpengl
            benchmarkOpengl.cpp)


    handleExternals(NAME google_benchmark)
    target_link_libraries(benchmarkOpengl
            guiBackend
            ${google_benchmark})

    #Add the Fonts to the output folder for benchmark
    file(COPY ${CMAKE_CURRENT_LIST_DIR}/../libs/fonts/
            DESTINATION ${CMAKE_BINARY_DIR}/test/fonts/)

endif ()

if (${PROJECT_NAME}_TEST_UNIT_TESTS)
    add_executable(testGLFWOpengl testGLFWOpengl.cpp)
    add_executable(testFontStorage testFontStorage.cpp)

    handleExternals(NAME doctest)

    target_compile_features(testGLFWOpengl PRIVATE cxx_std_17)
    target_compile_features(testFontStorage PRIVATE cxx_std_17)

    #link the test executable against the created libraries
    target_link_libraries(testGLFWOpengl
            PUBLIC
                doctest
                guiBackend
            )

    target_link_libraries(testFontStorage
            PUBLIC
                doctest
                guiBackend
            )

    enable_testing()
    include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
    doctest_discover_tests(testGLFWOpengl)
    doctest_discover_tests(testFontStorage)

    #Add the Fonts to the output folder for test
    file(COPY ${CMAKE_CURRENT_LIST_DIR}/../libs/fonts/
            DESTINATION ${CMAKE_BINARY_DIR}/test/bin/fonts/)
endif ()