add_library(AVLTree AVLTree.c)
target_link_libraries(AVLTree PRIVATE structure_compiler_flags Trace)
target_include_directories(AVLTree INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})