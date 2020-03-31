add_executable(sdltest sdltest.cpp)
target_link_libraries(sdltest ${SDL2_LIBRARIES})
add_test(sdltest_test sdltest)
