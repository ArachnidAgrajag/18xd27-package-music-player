cmake_minimum_required(VERSION 3.13)
project(MusicPlayer)  

include(CTest)
enable_testing()
set(EXEC MyMusicPlayer)
find_package(SDL2 REQUIRED)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

# No FindSDL2_mixer.cmake in Ubuntu 16.04?
# find_package(SDL2_mixer REQUIRED)
# Use pkg-config instead
find_package(PkgConfig)
# Using an underscore like SDL2_mixer doesn't work
pkg_check_modules(SDL2mixer REQUIRED SDL2_mixer)

include_directories(
  ${SDL2_INCLUDE_DIRS}
  ${SDL2mixer_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(test)

# puts all .cpp files inside src to the SOURCES variable
file(GLOB SOURCES src/*.cpp)

add_executable(${EXEC} ${SOURCES})

target_link_libraries( ${EXEC} 
    ${SDL2_LIBRARIES} 
    ${SDL2mixer_LIBRARIES}
    ${playFile}
    )
