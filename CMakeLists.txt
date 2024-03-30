cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(Structure VERSION 1.0)

enable_testing()
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
# TODO 4: Replace the following code by:
# * Creating an interface library called tutorial_compiler_flags
#   Hint: use add_library() with the INTERFACE signature
# * Add compiler feature cxx_std_11 to tutorial_compiler_flags
#   Hint: Use target_compile_features()

find_program(BASH_EXECUTABLE NAMES bash REQUIRED)

add_library(structure_compiler_flags INTERFACE)
target_compile_features(structure_compiler_flags INTERFACE c_std_99)
target_compile_options(structure_compiler_flags INTERFACE "-g;-Wall;-Wextra;-Wpedantic;-Wshadow;-Wconversion;-fsanitize=undefined,address;-Wfloat-equal;-Wformat-nonliteral;-Wformat-security;-Wformat-y2k;-Wformat=2;-Wimport;-Winvalid-pch;-Wlogical-op;-Wmissing-declarations;-Wmissing-field-initializers;-Wmissing-format-attribute;-Wmissing-include-dirs;-Wmissing-noreturn;-Wnested-externs;-Wpacked;-Wpointer-arith;-Wredundant-decls;-Wstack-protector;-Wswitch-enum;-Wundef;-Wwrite-strings")
add_subdirectory(trace)
add_subdirectory(ArrayList)
add_subdirectory(DoubleLinkedList)
add_subdirectory(CircularLinkedList)
add_subdirectory(LinkedList)
add_subdirectory(SymmetricMatrix)

add_subdirectory(test/ArrayList)
add_subdirectory(test/DoubleLinkedList)
add_subdirectory(test/CircularLinkedList)
add_subdirectory(test/LinkedList)
add_subdirectory(test/SymmetricMatrix)