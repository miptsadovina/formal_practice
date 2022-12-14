#include "Grammar.h"

struct CYK{
    Grammar g;
    CYK(Grammar& grammar) : g(grammar) {}
    void CYK_algorithm(const std::string& word);
};