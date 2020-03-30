cmake_minimum_required(VERSION 3.13.4)
#project name
project(MusicPlayer VERSION 0.0)
#executable name
set(EXEC MusicPlayer)
#headers
include_directories(includes)
#cpp files
file(GLOB STRINGS src.*.cpp)
#compiles 
add_executable(${EXEC} ${SOURCES})
