add_test( Earley_tests.test1 /Users/sadovinama/CLionProjects/first_algorithm/cmake-build-debug/tests/Earley_tests/unit_tests [==[--gtest_filter=Earley_tests.test1]==] --gtest_also_run_disabled_tests)
set_tests_properties( Earley_tests.test1 PROPERTIES WORKING_DIRECTORY /Users/sadovinama/CLionProjects/first_algorithm/cmake-build-debug/tests/Earley_tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( Earley_tests.test2 /Users/sadovinama/CLionProjects/first_algorithm/cmake-build-debug/tests/Earley_tests/unit_tests [==[--gtest_filter=Earley_tests.test2]==] --gtest_also_run_disabled_tests)
set_tests_properties( Earley_tests.test2 PROPERTIES WORKING_DIRECTORY /Users/sadovinama/CLionProjects/first_algorithm/cmake-build-debug/tests/Earley_tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( Earley_tests.test3 /Users/sadovinama/CLionProjects/first_algorithm/cmake-build-debug/tests/Earley_tests/unit_tests [==[--gtest_filter=Earley_tests.test3]==] --gtest_also_run_disabled_tests)
set_tests_properties( Earley_tests.test3 PROPERTIES WORKING_DIRECTORY /Users/sadovinama/CLionProjects/first_algorithm/cmake-build-debug/tests/Earley_tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( unit_tests_TESTS Earley_tests.test1 Earley_tests.test2 Earley_tests.test3)
