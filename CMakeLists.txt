cmake_minimum_required(VERSION 3.13)
project(MusicPlayer)  

include(CTest)
enable_testing()
set(EXEC MyMusicPlayer)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(test)

# puts all .cpp files inside src to the SOURCES variable
file(GLOB SOURCES src/*.cpp)

add_executable(${EXEC} ${SOURCES})
