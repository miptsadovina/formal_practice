#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <deque>
#include <queue>

//in struct Grammar declared set of transitions
struct Grammar {
    int start;
    int eps = 1;
    bool is_conclusion_eps = false;
    std::map<int, std::set<std::vector<int>>> transitions;
    std::set<int> alpabet;
    std::set<int> nonterminals;
    Grammar(int start, const std::map<int, std::set<std::vector<int>>> transitions, const std::set<int>& alphabet, const std::set<int>& nonterminals)
            : start(start), transitions(transitions), alpabet(alphabet), nonterminals(nonterminals) {}
    void add_transition(int from, std::set<std::string>& to);
    bool is_generative(int nonterm);
    bool is_achievable(int start, int nonterm);
    void first_step_CNF();
    void second_step_CNF();
    void third_step_CNF();
    void fourth_step_CNF();
    void fifth_step_CNF();
    bool is_conclusion_empty_word(int nonterm);
    void sixth_step_CNF();
    void seventh_step_CNF();
    void del_empty_word_rules();
    bool in_language(const std::string& word);
    void to_CNF();
};