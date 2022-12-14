#include "Grammar.h"

struct state{
    std::vector<int> rule;
    int index_point;
    int i;
    state(std::vector<int>& rule, int index_point, int i) :
            rule(rule), index_point(index_point), i(i) {}
};

struct Parser {
    Grammar g;
    const std::string& word;
    std::vector<std::set<std::pair<int, state>>> D;
    Parser(Grammar& grammar,const std::string& word) : g(grammar), word(word) {}
    void Earley();
    void scan(int j);
    bool predict(int j);
    bool complete(int j);
};