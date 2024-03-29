add_library(Trace trace.c _trace_ArrayList.c)
target_link_libraries(Trace PRIVATE structure_compiler_flags)
target_include_directories(Trace INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})