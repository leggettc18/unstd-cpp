cmake_minimum_required(VERSION 3.14...3.25)

project(
  UnStdLibrary
  VERSION 0.1.0
  DESCRIPTION
    "An implementation of various C++ Standard Library Featurs and Data Structures (mostly done for fun and learning)."
  LANGUAGES CXX)

# Only do the following pieces if this is the main project.
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Optionally set CMAKE_CXX_STANDARD and other settings here
  set(default_build_type "Release")
  if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(
      STATUS
        "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE
        "${default_build_type}"
        CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                                 "MinSizeRel" "RelWithDebInfo")
  endif()

  set(CMAKE_CXX_EXTENSION OFF)

  # Support Folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  include(CTest)

  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
endif()

add_subdirectory(src)
add_subdirectory(apps)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
   AND BUILD_TESTING)
  # add_subdirectory(tests)
endif()
