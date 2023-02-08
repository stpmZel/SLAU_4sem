cmake_minimum_required(VERSION 3.24)

project(pass_method_lib_test)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(
        pass_method_lib_test
        pass_method_lib_test.cc
)
target_link_libraries(
        pass_method_lib_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(pass_method_lib_test)


#target_link_libraries(pass_method_lib_test gtest gmock pthread)
#
#set_target_properties(pass_method_lib PROPERTIES LINKER_LANGUAGE CXX)
