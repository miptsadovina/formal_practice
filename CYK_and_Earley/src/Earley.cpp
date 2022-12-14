#include "Earley.h"
#include <algorithm>

bool operator<(const state& one, const state& two) {
    return one.rule < two.rule;
}

void Parser::Earley() {
    g.to_CNF();
    int size = word.size();
    D.resize(size + 1);
    int new_start = std::max(*(g.nonterminals.rbegin()) + 1, *(g.alpabet.rbegin()) + 1);
    std::vector<int> tmp = {'.', g.start};
    g.transitions[new_start].insert({g.start});
    g.nonterminals.insert(new_start);
    D[0].insert({new_start,state(tmp, 0, 0)});
    for(int j = 0; j <= size; ++j) {
        scan(j);
        bool changes = true;
        while(changes) {
            changes = false;
            changes = complete(j);
            changes = changes || predict(j);
        }
    }
    std::vector<int> help = {g.start, '.'};
    if(D[size].contains({new_start, state(help, 1, 0)})) {
        std::cout <<  1;
    } else {
        std::cout << 0;
    }
}

void Parser::scan(int j) {
    if (j == 0) {
        return;
    }
    for(auto& context: D[j - 1]) {
        if(context.second.index_point + 1 < context.second.rule.size() &&
            context.second.rule[context.second.index_point + 1] == word[j - 1]) {
            std::pair<int, state> tmp = context;
            std::swap(tmp.second.rule[tmp.second.index_point], tmp.second.rule[++tmp.second.index_point]);
            D[j].insert(tmp);
        }
    }
}

bool Parser::complete(int j) {
    bool res = false;
    for(auto& context1: D[j]) {
        if(context1.second.index_point != context1.second.rule.size() - 1) {
            continue;
        }
        for(auto& context2: D[context1.second.i]) {
            if(context2.second.index_point + 1 < context2.second.rule.size() &&
                        context1.first == context2.second.rule[context2.second.index_point + 1]) {
                std::pair<int, state> tmp = context2;
                std::swap(tmp.second.rule[tmp.second.index_point], tmp.second.rule[++tmp.second.index_point]);
                if(!D[j].contains(tmp)) {
                    D[j].insert(tmp);
                    res = true;
                }
            }
        }
    }
    return res;
}

bool Parser::predict(int j) {
    bool res = false;
    for(auto& context: D[j]) {
        if(context.second.index_point + 1 == context.second.rule.size()) {
            continue;
        }
        int nonterm = context.second.rule[context.second.index_point + 1];
        if(!g.nonterminals.contains(nonterm)) {
            continue;
        }
        for(auto& right_word: g.transitions[nonterm]) {
            std::vector<int> tmp = {'.'};
            for(int i = 0; i < right_word.size(); ++i) {
                tmp.push_back(right_word[i]);
            }
            state help(tmp, 0, j);
            if(!D[j].contains({nonterm, help})) {
                D[j].insert({nonterm, help});
                res = true;
            }
        }
    }
    return res;
}