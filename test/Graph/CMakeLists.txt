add_executable(testGraph testGraph.c)
target_link_libraries(testGraph PRIVATE asan ubsan structure_compiler_flags Graph)
add_executable(testGraphMst testGraphMst.c)
target_link_libraries(testGraphMst PRIVATE asan ubsan structure_compiler_flags Graph)

add_test(NAME testGraph COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/outputCompare.sh ${CMAKE_CURRENT_BINARY_DIR}/testGraph ${CMAKE_CURRENT_SOURCE_DIR}/testGraph.in ${CMAKE_CURRENT_SOURCE_DIR}/testGraph.out")
add_test(NAME testGraphMst COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/outputCompare.sh ${CMAKE_CURRENT_BINARY_DIR}/testGraphMst ${CMAKE_CURRENT_SOURCE_DIR}/testGraphMst.in ${CMAKE_CURRENT_SOURCE_DIR}/testGraphMst.out")
