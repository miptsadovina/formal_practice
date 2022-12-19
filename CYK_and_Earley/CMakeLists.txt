cmake_minimum_required(VERSION 3.20)
project(CYK_and_Earley)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS --coverage)

add_executable(unit_tests tests/CYK_tests.cpp tests/Earley_tests.cpp
        src/Grammar.h src/Grammar.cpp
        src/CYK_algorithm.cpp src/CYK_algorithm.h
        src/Earley.cpp src/Earley.h)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
enable_testing()

target_link_libraries(
        unit_tests
        GTest::gtest_main
)

include(GoogleTest)