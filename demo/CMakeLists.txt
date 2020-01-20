cmake_minimum_required(VERSION 3.15)
project(emusound_demo)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp EmuAudioSource.cpp EmuAudioSource.h)

add_executable(emusound_demo ${SOURCE_FILES})

target_link_libraries(emusound_demo ${PROJECT_SOURCE_DIR}/../external_libs/lib/linux/libsoloud-s-d.a pthread asound)