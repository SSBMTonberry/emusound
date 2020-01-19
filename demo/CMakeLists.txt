cmake_minimum_required(VERSION 3.15)
project(emusound_demo)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp)

add_executable(emusound_demo ${SOURCE_FILES})
target_link_libraries(emusound_demo emusound ${SOURCE_FILES})