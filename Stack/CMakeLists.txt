add_library(Stack Stack.c)
target_link_libraries(Stack PRIVATE structure_compiler_flags)
target_include_directories(Stack INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})