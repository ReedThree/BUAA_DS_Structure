add_executable(testAVLTree testAVLTree.c)
target_link_libraries(testAVLTree PRIVATE asan ubsan structure_compiler_flags AVLTree Trace)

add_test(NAME testAVLTree COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/outputCompare.sh ${CMAKE_CURRENT_BINARY_DIR}/testAVLTree X ${CMAKE_CURRENT_SOURCE_DIR}/testAVLTree.out")
