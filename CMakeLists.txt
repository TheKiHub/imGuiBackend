#set minimum Cmake Version and set new policy since its faster and we use modern cmake
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(guiBackend VERSION 0.1.0 LANGUAGES CXX C)

# only initialize all the basic stuff when this is the main project or when the basic project don't initialize it
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR NO_BASIC_INITIAL_IN_ROOT)
   # check if there is a connection to the internet if not only use the cache
   # when cmake is done by github actions we can't use ping here, but we must be online anyway
   if (NOT GITHUB_ACTION_TRIGGER)
      if (MSVC)
         execute_process(COMMAND ping www.github.com -n 1 ERROR_QUIET RESULT_VARIABLE NO_CONNECTION)
      else()
         execute_process(COMMAND ping www.github.com -c 1 ERROR_QUIET RESULT_VARIABLE NO_CONNECTION)
      endif()

      if (NOT NO_CONNECTION EQUAL 0)
         set(FETCHCONTENT_FULLY_DISCONNECTED ON)
         message(WARNING "Fetch offline mode: requires already populated or cached _deps")
      else()
         set(FETCHCONTENT_FULLY_DISCONNECTED OFF)
         if (NOT DEFINED "${FETCH_BRANCH}")
            set(FETCH_BRANCH origin/master CACHE STRING "Branch for internal fetching")
         endif()
      endif()
   endif()

   if(POLICY CMP0135)
      cmake_policy(SET CMP0135 NEW) # set fetch timestamp behavior to new policy
   endif()
   include(FetchContent)
   FetchContent_Declare(
           cmakeBase
           URL https://github.com/TheKiHub/cmakeBase/releases/latest/download/package_files.zip
           SOURCE_DIR cmakeBase
   )
   FetchContent_GetProperties(cmakeBase)
   if(NOT cmakeBase_POPULATED)
      FetchContent_Populate(cmakeBase)
      include(${CMAKE_CURRENT_BINARY_DIR}/cmakeBase/CMakeLists.txt)
   endif()

   # if this was just for initialize the basic stuff don't add the app and tests and reset the initial force
   if(NOT NO_BASIC_INITIAL_IN_ROOT)
      add_subdirectory(app)

      # unit tests should be on if this is the main project
      option(${PROJECT_NAME}_ENABLE_UNIT_TESTS "Enable the unit tests for ${projectName}" ON)

      if (${PROJECT_NAME}_ENABLE_UNIT_TESTS)
         add_subdirectory(test)
      endif ()
   else()
      SET(NO_BASIC_INITIAL_IN_ROOT OFF)
   endif()
endif ()

#add the code
add_subdirectory(libs)
