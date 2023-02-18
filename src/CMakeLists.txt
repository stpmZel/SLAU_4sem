cmake_minimum_required(VERSION 3.24)
project(SLAU_LIB)


set(CMAKE_CXX_STANDARD 23)

add_compile_options(-Wall -Werror)

file(GLOB_RECURSE source *.h)
add_library(SLAU_LIB INTERFACE libB.cpp)