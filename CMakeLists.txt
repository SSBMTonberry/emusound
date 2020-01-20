cmake_minimum_required(VERSION 3.15)
project(emusound)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)
set(CMAKE_CXX_FLAGS -DSFML_STATIC)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSFML_STATIC -DEBOX_DEBUG")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Choose the type of build, options are: Debug Release
RelWithDebInfo MinSizeRel."
            FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEBUG 1)
    message(DEBUGGIN')
else()
    set(RELEASE 1)
endif()

set(ESND_LINUX 0)
set(ESND_WINDOWS 0)
set(ESND_APPLE 0)
set(ESND_MSVC 0)
set(ESND_MINGW 0)

if(UNIX AND NOT APPLE)
    set(ESND_LINUX 1)
elseif(APPLE)
    link_directories(/usr/local/opt/llvm/lib/)
    set(ESND_APPLE 1)
elseif(WIN32)
    set(ESND_WINDOWS 1)
    if(MSVC)
        set(ESND_MSVC 1)
    elseif(MINGW)
        set(ESND_MINGW 1)
    endif()
endif()

if(DEBUG)
    message("Adding debug submodules")
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/source/caudio ${PROJECT_SOURCE_DIR}/external_libs/source/caudio/cmake-build-debug)
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/source/pmgui/src ${PROJECT_SOURCE_DIR}/external_libs/source/pmgui/cmake-build-debug)
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/source/sfml ${PROJECT_SOURCE_DIR}/external_libs/source/sfml/cmake-build-debug)
else()
    message("Adding release submodules")
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/source/caudio ${PROJECT_SOURCE_DIR}/external_libs/source/caudio/cmake-build-release)
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/source/pmgui/src ${PROJECT_SOURCE_DIR}/external_libs/source/pmgui/cmake-build-release)
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/source/sfml ${PROJECT_SOURCE_DIR}/external_libs/source/sfml/cmake-build-release)
endif()

configure_file (
        "${PROJECT_SOURCE_DIR}/EmusoundConfig.h.in"
        "${PROJECT_SOURCE_DIR}/EmusoundConfig.h"
)

#configure_file(
#        "${PROJECT_SOURCE_DIR}/external_libs/source/caudio/CMake/Templates/cAudioBuildSettings.h.in"
#        "${PROJECT_SOURCE_DIR}/external_libs/source/caudio/cAudio/include/cAudioBuildSettings.h"
#)

set(SOURCE_FILES main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/external_libs/include/ ${PROJECT_SOURCE_DIR}/external_libs/source/)
add_library(emusound STATIC ${SOURCE_FILES})
target_link_libraries(emusound ${SOURCE_FILES})

add_subdirectory(demo)