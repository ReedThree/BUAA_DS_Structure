add_library(Graph Graph.c)
target_link_libraries(Graph PRIVATE structure_compiler_flags)
target_include_directories(Graph INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})