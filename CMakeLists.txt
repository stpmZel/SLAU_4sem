cmake_minimum_required(VERSION 3.24)
project(SLAU_LIB)


set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(main solvers_data.cpp)
