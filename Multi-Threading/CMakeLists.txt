cmake_minimum_required(VERSION 3.10)
project(Multi_Threading C)

set(CMAKE_C_STANDARD 11)
find_library(pthread NAMES pthread.h)
link_libraries(pthread)
add_executable(Multi_Threading main.c)