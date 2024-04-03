add_executable(testQueue testQueue.c)
target_link_libraries(testQueue PRIVATE asan ubsan structure_compiler_flags Queue)

add_test(NAME testQueue COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/outputCompare.sh ${CMAKE_CURRENT_BINARY_DIR}/testQueue X ${CMAKE_CURRENT_SOURCE_DIR}/Queue.out")
