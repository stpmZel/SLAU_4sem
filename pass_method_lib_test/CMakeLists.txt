cmake_minimum_required(VERSION 3.24)

project(pass_method_lib_test)

set(CMAKE_CXX_STANDARD 20)


add_executable(
        pass_method_lib_test
        pass_method_lib_test.cpp
)


target_link_libraries(pass_method_lib_test gtest gtest_main)





