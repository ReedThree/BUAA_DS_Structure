add_executable(testBinarySearchTree testBinarySearchTree.c)
target_link_libraries(testBinarySearchTree PRIVATE asan ubsan structure_compiler_flags AbstractBinaryTree BinarySearchTree Trace)

add_test(NAME testBinarySearchTree COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/outputCompare.sh ${CMAKE_CURRENT_BINARY_DIR}/testBinarySearchTree X ${CMAKE_CURRENT_SOURCE_DIR}/testBinarySearchTree.out")
