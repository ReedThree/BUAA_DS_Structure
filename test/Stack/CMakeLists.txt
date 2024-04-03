add_executable(testStackFixedSize testStackFixedSize.c)
target_link_libraries(testStackFixedSize PRIVATE asan ubsan structure_compiler_flags Stack)

add_executable(testStackDynamicSize testStackDynamicSize.c)
target_link_libraries(testStackDynamicSize PRIVATE asan ubsan structure_compiler_flags Stack)

add_test(NAME testStackFixedSize COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/outputCompare.sh ${CMAKE_CURRENT_BINARY_DIR}/testStackFixedSize X ${CMAKE_CURRENT_SOURCE_DIR}/StackFixedSize.out")
add_test(NAME testStackDynamicSize COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/outputCompare.sh ${CMAKE_CURRENT_BINARY_DIR}/testStackDynamicSize X ${CMAKE_CURRENT_SOURCE_DIR}/StackDynamicSize.out")
