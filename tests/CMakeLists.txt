
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_subdirectory(Google_tests/lib)


add_executable(test_1 pass_method_lib_test.cpp)
add_test(test_1 COMMAND pass_method_lib_test.cpp)
target_link_libraries(test_1 gtest gtest_main)






