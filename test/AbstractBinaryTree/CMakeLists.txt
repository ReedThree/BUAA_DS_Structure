add_executable(testAbstractBinaryTree testAbstractBinaryTree.c)
target_link_libraries(testAbstractBinaryTree PRIVATE asan ubsan structure_compiler_flags AbstractBinaryTree Trace)


add_test(NAME testAbstractBinaryTree COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/outputCompare.sh ${CMAKE_CURRENT_BINARY_DIR}/testAbstractBinaryTree X ${CMAKE_CURRENT_SOURCE_DIR}/testHashTableBasic.out")
