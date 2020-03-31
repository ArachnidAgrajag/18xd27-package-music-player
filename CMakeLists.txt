cmake_minimum_required(VERSION 3.13)
project(MusicPlayer)  

include(CTest)
enable_testing()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
