cmake_minimum_required(VERSION 3.9)
project(LangtonsAnt C)

set(CMAKE_C_STANDARD 11)

add_executable(LangtonsAnt main.c dynamicArray.h dynamicArray.c qdbmp.c)