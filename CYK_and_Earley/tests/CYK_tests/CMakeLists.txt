cmake_minimum_required(VERSION 3.21)
project(CYK)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS --coverage)

add_executable(unit_tests CYK_tests.cpp
        ../../src/Grammar.h ../../src/Grammar.cpp
        ../../src/CYK_algorithm.h ../../src/CYK_algorithm.cpp)

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
gtest_discover_tests(unit_tests)