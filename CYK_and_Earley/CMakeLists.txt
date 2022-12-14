cmake_minimum_required(VERSION 3.21)
project(CYK_and_Earley)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(tests/CYK_tests)
add_subdirectory(tests/Earley_tests)

add_executable(CYK_and_Earley
        src/Grammar.h src/Grammar.cpp
        src/CYK_algorithm.h src/CYK_algorithm.cpp
        src/Earley.h src/Earley.cpp)
