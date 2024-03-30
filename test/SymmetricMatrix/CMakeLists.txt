function(testSymmetricMatrix part result)
add_executable(SymmetricMatrix_${part} ${part}.c)
target_link_libraries(SymmetricMatrix_${part} PRIVATE asan ubsan structure_compiler_flags Trace SymmetricMatrix)
add_test(NAME SymmetricMatrix_${part} COMMAND ${BASH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.sh $<TARGET_FILE:SymmetricMatrix_${part}> ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(SymmetricMatrix_${part} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endfunction()

testSymmetricMatrix("testSymmetricMatrix" "10.00\n1.00 2.00 4.00 7.00 11.00\n2.00 3.00 3.00 8.00 12.00\n4.00 3.00 6.00 9.00 13.00\n7.00 8.00 9.00 10.00 14.00\n11.00 12.00 13.00 14.00 10.00")
