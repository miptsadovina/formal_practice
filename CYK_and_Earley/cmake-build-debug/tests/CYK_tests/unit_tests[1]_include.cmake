if(EXISTS "/Users/sadovinama/CLionProjects/first_algorithm/cmake-build-debug/tests/CYK_tests/unit_tests[1]_tests.cmake")
  include("/Users/sadovinama/CLionProjects/first_algorithm/cmake-build-debug/tests/CYK_tests/unit_tests[1]_tests.cmake")
else()
  add_test(unit_tests_NOT_BUILT unit_tests_NOT_BUILT)
endif()
