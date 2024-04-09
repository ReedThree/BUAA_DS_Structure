add_executable(testHashTableBasic testHashTableBasic.c)
target_link_libraries(testHashTableBasic PRIVATE asan ubsan structure_compiler_flags HashTable Trace)

add_executable(testHashTableCollision testHashTableCollision.c)
target_link_libraries(testHashTableCollision PRIVATE asan ubsan structure_compiler_flags HashTable Trace)

add_test(NAME testHashTableBasic COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/outputCompare.sh ${CMAKE_CURRENT_BINARY_DIR}/testHashTableBasic X ${CMAKE_CURRENT_SOURCE_DIR}/testHashTableBasic.out")
add_test(NAME testHashTableCollision COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/outputCompare.sh ${CMAKE_CURRENT_BINARY_DIR}/testHashTableCollision X ${CMAKE_CURRENT_SOURCE_DIR}/testHashTableCollision.out")