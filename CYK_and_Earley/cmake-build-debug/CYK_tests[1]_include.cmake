if(EXISTS "/Users/sadovinama/CLionProjects/first_algorithm/cmake-build-debug/CYK_tests[1]_tests.cmake")
  include("/Users/sadovinama/CLionProjects/first_algorithm/cmake-build-debug/CYK_tests[1]_tests.cmake")
else()
  add_test(CYK_tests_NOT_BUILT CYK_tests_NOT_BUILT)
endif()
