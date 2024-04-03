add_library(Queue Queue.c)
target_link_libraries(Queue PRIVATE structure_compiler_flags)
target_include_directories(Queue INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})