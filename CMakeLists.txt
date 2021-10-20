cmake_minimum_required(VERSION 3.17)
project(cube C)


set(CMAKE_C_STANDARD 99)

add_executable(cube cube.c)


target_link_libraries(cube -lOpenGL32 -lfreeGLUT -lGLU32)
