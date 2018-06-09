cmake_minimum_required(VERSION 3.10)
project(Scheduling C)

set(CMAKE_C_STANDARD 11)
find_library(pthread NAMES pthread.h)
link_libraries(pthread)
add_executable(Scheduling main.c lists.h)