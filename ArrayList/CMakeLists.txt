add_library(ArrayList ArrayList.c)
target_link_libraries(ArrayList PRIVATE structure_compiler_flags Trace)
target_include_directories(ArrayList INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})