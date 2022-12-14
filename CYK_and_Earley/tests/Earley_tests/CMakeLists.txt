cmake_minimum_required(VERSION 3.21)
project(Earley)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS --coverage)

add_executable(unit_tests Earley_tests.cpp
        ../../src/Grammar.h ../../src/Grammar.cpp
        ../../src/Earley.h ../../src/Earley.cpp)

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