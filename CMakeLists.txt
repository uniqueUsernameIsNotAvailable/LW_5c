cmake_minimum_required(VERSION 3.21)
project(LW_5c C)

set(CMAKE_C_STANDARD 11)

add_executable(LW_5c main.c libs/additional.c libs/additional.h)
