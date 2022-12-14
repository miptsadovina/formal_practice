#include "gtest/gtest.h"
#include "../../src/Earley.h"

TEST(Earley_tests, test1) {
    testing::internal::CaptureStdout();
    int start = 'S';
    std::map<int, std::set<std::vector<int>>> rules;
    rules['S'] = {{'a', 'F', 'b', 'F'}};
    rules['F'] = {{'a', 'F', 'b'}, {1}, {'G', 'a'}};
    rules['G'] = {{'b', 'S', 'G'}};
    std::set<int> alpabet = {'a', 'b', 1};
    std::set<int> nonterminals = {'S', 'F', 'G'};
    Grammar grammar(start, rules, alpabet, nonterminals);
    Parser parser(grammar, "abaabb");
    parser.Earley();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("1", output);
}

TEST(Earley_tests, test2) {
    testing::internal::CaptureStdout();
    int start = 'S';
    std::map<int, std::set<std::vector<int>>> rules;
    rules['S'] = {{'a', 'F', 'F'}};
    rules['F'] = {{'a', 'F', 'b'}, {1}, {'G', 'b', 'a'}};
    rules['G'] = {{'b', 'S', 'a', 'G'}};
    std::set<int> alpabet = {'a', 'b', 1};
    std::set<int> nonterminals = {'S', 'F', 'G'};
    Grammar grammar(start, rules, alpabet, nonterminals);
    Parser parser(grammar, "aabab");
    parser.Earley();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("1", output);
}

TEST(Earley_tests, test3) {
    testing::internal::CaptureStdout();
    int start = 'S';
    std::map<int, std::set<std::vector<int>>> rules;
    rules['S'] = {{'a', 'F', 'F'}};
    rules['F'] = {{'a', 'F', 'b'}, {1}, {'G', 'b', 'a'}};
    rules['G'] = {{'b', 'S', 'a', 'G', 'E'}};
    rules['E'] = {{'a'}, {'b'}, {1}};
    std::set<int> alpabet = {'a', 'b', 1};
    std::set<int> nonterminals = {'S', 'F', 'G'};
    Grammar grammar(start, rules, alpabet, nonterminals);
    Parser parser(grammar, "aabbbaabbab");
    parser.Earley();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("0", output);
}

TEST(Earley_tests, test4) {
    testing::internal::CaptureStdout();
    int start = 'S';
    std::map<int, std::set<std::vector<int>>> rules;
    rules['S'] = {{'a', 'F', 'b', 'F'}};
    rules['F'] = {{'a', 'F', 'b'}};
    std::set<int> alpabet = {'a', 'b', 1};
    std::set<int> nonterminals = {'S', 'F'};
    Grammar grammar(start, rules, alpabet, nonterminals);
    Parser parser(grammar, "abaabb");
    parser.Earley();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("0", output);
}

TEST(Earley_tests, test5) {
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
    Parser parser(grammar, "aabbaabbab");
    parser.Earley();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("0", output);
}