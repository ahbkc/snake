cmake_minimum_required(VERSION 3.14)
project(c_sdl_demo C)

set(CMAKE_C_STANDARD 99)
find_package(PkgConfig REQUIRED)

add_executable(c_sdl_demo main.c)
target_link_libraries(c_sdl_demo SDL2)