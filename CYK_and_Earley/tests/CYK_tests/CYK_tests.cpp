#include "gtest/gtest.h"
#include "../../src/CYK_algorithm.h"

TEST(CYK_tests, test1) {
    testing::internal::CaptureStdout();
    int start = 'S';
    std::map<int, std::set<std::vector<int>>> rules;
    rules['S'] = {{'a', 'F', 'b', 'F'}};
    rules['F'] = {{'a', 'F', 'b'}, {1}, {'G', 'a'}};
    rules['G'] = {{'b', 'S', 'G'}};
    std::set<int> alpabet = {'a', 'b', 1};
    std::set<int> nonterminals = {'S', 'F', 'G'};
    Grammar grammar(start, rules, alpabet, nonterminals);
    CYK cyk_algo(grammar);
    cyk_algo.CYK_algorithm("abaabb");
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("1", output);
}

TEST(CYK_tests, test2) {
    testing::internal::CaptureStdout();
    int start = 'S';
    std::map<int, std::set<std::vector<int>>> rules;
    rules['S'] = {{'a', 'F', 'F'}};
    rules['F'] = {{'a', 'F', 'b'}, {1}, {'G', 'b', 'a'}};
    rules['G'] = {{'b', 'S', 'a', 'G'}};
    std::set<int> alpabet = {'a', 'b', 1};
    std::set<int> nonterminals = {'S', 'F', 'G'};
    Grammar grammar(start, rules, alpabet, nonterminals);
    CYK cyk_algo(grammar);
    cyk_algo.CYK_algorithm("aabab");
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("1", output);
}

TEST(CYK_tests, test3) {
    testing::internal::CaptureStdout();
    int start = 'S';
    std::map<int, std::set<std::vector<int>>> rules;
    rules['S'] = {{'a', 'F', 'F'}};
    rules['F'] = {{'a', 'F', 'b'}, {1}, {'G', 'b', 'a'}};
    rules['G'] = {{'b', 'S', 'a', 'G', 'E'}};
    rules['E'] = {{'a'}, {'b'}, {1}};
    std::set<int> alpabet = {'a', 'b', 1};
    std::set<int> nonterminals = {'S', 'F', 'G', 'E'};
    Grammar grammar(start, rules, alpabet, nonterminals);
    CYK cyk_algo(grammar);
    cyk_algo.CYK_algorithm("aabbbaabbab");
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("0", output);
}

TEST(CYK_tests, test4) {
    testing::internal::CaptureStdout();
    int start = 'S';
    std::map<int, std::set<std::vector<int>>> rules;
    rules['S'] = {{'a', 'F', 'b', 'F'}};
    rules['F'] = {{'a', 'F', 'b'}};
    std::set<int> alpabet = {'a', 'b', 1};
    std::set<int> nonterminals = {'S', 'F'};
    Grammar grammar(start, rules, alpabet, nonterminals);
    CYK cyk_algo(grammar);
    cyk_algo.CYK_algorithm("abaabb");
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("0", output);
}

TEST(CYK_tests, test5) {
    testing::internal::CaptureStdout();
    int start = 'S';
    std::map<int, std::set<std::vector<int>>> rules;
    rules['S'] = {{'a', 'F', 'F'}};
    rules['F'] = {{'a', 'F', 'b'}, {1}, {'G', 'b', 'a'}};
    rules['G'] = {{'b', 'S', 'a', 'G'}};
    rules['E'] = {{'b', 'S'}};
    rules['T'] = {{'a', 'G'}};
    std::set<int> alpabet = {'a', 'b', 1};
    std::set<int> nonterminals = {'S', 'F', 'G', 'E', 'T'};
    Grammar grammar(start, rules, alpabet, nonterminals);
    CYK cyk_algo(grammar);
    cyk_algo.CYK_algorithm("aabbaabbab");
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("0", output);
}