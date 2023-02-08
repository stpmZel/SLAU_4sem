project(pass_method_lib)

set(HEADER_FILES pass_method_lib.h)

add_library(pass_method_lib ${HEADER_FILES})

set_target_properties(pass_method_lib PROPERTIES LINKER_LANGUAGE CXX)