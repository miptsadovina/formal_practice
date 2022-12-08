#include "ChomskyNormalForm.h"

void Grammar::first_step_CNF() { // delete non generative symbols
    std::set<int> non_generative;
    for(auto nonterm : nonterminals) {
        if (!is_generative(nonterm)) {
            non_generative.insert(nonterm);
        }
    }
    for(auto nonterm: non_generative) {
        transitions.erase(nonterm);
        nonterminals.erase(nonterm);
    }
    for(auto& rule: transitions) {
        std::set<std::vector<int>> erase_word;
        for(auto& word: rule.second) {
            for(auto letter: word) {
                if(non_generative.contains(letter)) {
                    erase_word.insert(word);
                    break;
                }
            }
        }
        for(auto& elem: erase_word) {
            rule.second.erase(elem);
        }
    }
}

bool Grammar::is_generative(int nonterm) {
    bool ans = true;
    for(const auto& word : transitions[nonterm]) {
        ans = true;
        for(auto letter : word) {
            if(letter == nonterm || (nonterminals.contains(letter) && !is_generative(letter))) {
                ans = false;
            }
        }
        if(ans) {
            return true;
        }
    }
    return false;
}

bool Grammar::is_achievable(int begin, int nonterm) {
    if (begin == nonterm) {
        return true;
    }
    bool ans = false;
    for(auto& word: transitions[begin]) {
        int num_eps = 0;
        for(auto letter: word) {
            if(letter == begin) {
                continue;
            }
            if(letter == eps) {
                ++num_eps;
            }
            if(nonterminals.contains(letter) && is_achievable(letter, nonterm)) {
                ans = true;
            }
        }
        if(num_eps == word.size()) {
            is_conclusion_eps = true;
        }
    }
    return ans;
}

//deleting unattainable symbols
void Grammar::second_step_CNF() {
    std::set<int> unattainable;
    for(auto nonterm: nonterminals) {
        if(!is_achievable(start, nonterm)) {
            unattainable.insert(nonterm);
        }
    }
    for(auto elem: unattainable) {
        transitions.erase(elem);
        nonterminals.erase(elem);
    }
    for(auto& rule: transitions) {
        std::set<std::vector<int>> erase_word;
        for(auto& word: rule.second) {
            for(auto letter: word) {
                if(unattainable.contains(letter)) {
                    erase_word.insert(word);
                    break;
                }
            }
        }
        for(auto& elem: erase_word) {
            rule.second.erase(elem);
        }
    }
}

//deleting mixed rules
void Grammar::third_step_CNF() {
    std::set<std::pair<int, std::vector<int>>> insert_rules;
    for(auto& rule: transitions) {
        std::set<std::vector<int>> erase_word;
        std::set<std::vector<int>> insert_word;
        std::set<int> insert_nonterm;
        for(auto& word: rule.second) {
            if(word.size() < 2) {
                continue;
            }
            std::vector<int> terms;
            std::vector<int> nonterms;
            for(auto letter: word) {
                if(alpabet.contains(letter)) {
                    terms.push_back(letter);
                } else if(nonterminals.contains(letter)) {
                    nonterms.push_back(letter);
                }
            }
            if(terms.empty() || nonterms.empty()) {
                continue;
            }
            std::vector<int> new_right_word;
            for(int i = 0; i < word.size(); ++i) {
                if(alpabet.contains(word[i])) {
                    int new_nonterm = std::max(*(alpabet.rbegin()) + 1 + i, *(nonterminals.rbegin()) + 1 + i);
                    new_right_word.push_back(new_nonterm);
                    insert_nonterm.insert(new_nonterm);
                    std::vector<int> letter_word = {word[i]};
                    insert_rules.insert({new_nonterm, letter_word});
                } else if(nonterminals.contains(word[i])) {
                    new_right_word.push_back(word[i]);
                }
            }
            insert_word.insert(new_right_word);
            erase_word.insert(word);
        }
        for(auto& elem: erase_word) {
            rule.second.erase(elem);
        }
        for(auto& elem: insert_word) {
            rule.second.insert(elem);
        }
        for(auto& elem: insert_nonterm) {
            nonterminals.insert(elem);
        }
    }
    for(auto& elem: insert_rules) {
        transitions[elem.first].insert(elem.second);
    }
}

//deleting long rules
void Grammar::fourth_step_CNF() {
    std::set<std::pair<int, std::vector<int>>> insert_rules;
    std::set<std::pair<int, std::vector<int>>> erase_rules;
    int k = 0;
    for(auto& rule: transitions) {
        for(auto& word: rule.second) {
            if(word.size() <= 2 || alpabet.contains(word[0])) {
                continue;
            }
            int cur_nonterm = rule.first;
            std::vector<int> new_word = word;
            for(long long i = word.size() - 1; i > 1; --i) {
                int new_nonterm = std::max(*(alpabet.rbegin()) + 1 + i + k, *(nonterminals.rbegin()) + 1 + i + k);
                std::vector<int> new_right_word = {new_nonterm, word[i]};
                insert_rules.insert({cur_nonterm, new_right_word});
                erase_rules.insert({cur_nonterm, new_word});
                new_word.pop_back();
                insert_rules.insert({new_nonterm, new_word});
                cur_nonterm = new_nonterm;
            }
            ++k;
        }
        ++k;
    }
    for(auto& elem: insert_rules) {
        transitions[elem.first].insert(elem.second);
        nonterminals.insert(elem.first);
    }
    for(auto& elem: erase_rules) {
        transitions[elem.first].erase(elem.second);
    }
}

bool Grammar::is_conclusion_empty_word(int nonterm) {
    if(!nonterminals.contains(nonterm)) {
        return false;
    }
    for(auto& word: transitions[nonterm]) {
        if(word.size() == 1) {
            if((alpabet.contains(word[0]) && word[0] == eps)
                || (nonterminals.contains(word[0]) && word[0] != nonterm
                    && is_conclusion_empty_word(word[0]))) {
                return true;
            }
        }
        if(word.size() == 2) {
            if(alpabet.contains(word[0]) && word[0] == word[1] && word[0] == eps) {
                return true;
            }
            if(nonterminals.contains(word[0]) && word[0] != nonterm && word[1] != nonterm
                && is_conclusion_empty_word(word[0]) && is_conclusion_empty_word(word[1])) {
                return true;
            }
        }
    }
    return false;
}

//deleting eps generating symbols
void Grammar::fifth_step_CNF() {
    std::set<std::pair<int, std::vector<int>>> insert_rules;
    for(auto& rule: transitions) {
        for(auto& word: rule.second) {
            if(word.size() != 2) {
                continue;
            }
            if(is_conclusion_empty_word(word[1])) {
                std::vector<int> new_right_word = {word[0]};
                insert_rules.insert({rule.first, new_right_word});
            }
            if(is_conclusion_empty_word(word[0])) {
                std::vector<int> new_right_word = {word[1]};
                insert_rules.insert({rule.first, new_right_word});
            }
        }
    }
    for(auto& elem: insert_rules) {
        transitions[elem.first].insert(elem.second);
    }
    del_empty_word_rules();
}

void Grammar::del_empty_word_rules() {
    for(auto nonterm: nonterminals) {
        transitions[nonterm].erase({eps});
        transitions[nonterm].erase({eps, eps});
    }
}

void Grammar::sixth_step_CNF() {
    if(is_conclusion_eps) {
        transitions[start].insert({eps});
    }
}

//deleting unary rules
void Grammar::seventh_step_CNF() {
    std::set<std::pair<int, std::vector<int>>> insert_rules;
    std::set<std::pair<int, std::vector<int>>> erase_rules;
    for(auto& rule: transitions) {
        for(auto& word: rule.second) {
            if(word.size() == 1 && !alpabet.contains(word[0])) {
                erase_rules.insert({rule.first, word});
                std::queue<int> q;
                q.push(word[0]);
                while(!q.empty()) {
                    int nonterm = q.front();
                    q.pop();
                    for(auto& new_word: transitions[nonterm]) {
                        if(new_word.size() == 1 && !alpabet.contains(new_word[0])) {
                            if(new_word[0] == nonterm) {
                                continue;
                            }
                            q.push(new_word[0]);
                        } else {
                            insert_rules.insert({rule.first, new_word});
                        }
                    }
                }
            }
        }
    }
    for(auto& elem: insert_rules) {
        transitions[elem.first].insert(elem.second);
    }
    for(auto& elem: erase_rules) {
        transitions[elem.first].erase(elem.second);
    }
}

//CYK algorithm
bool Grammar::in_language(const std::string& word) {
    int n = word.size();
    std::map<int, std::vector<std::vector<bool>>> dp;
    for(auto nonterm: nonterminals) {
        dp[nonterm] = std::vector<std::vector<bool>>(n, std::vector<bool>(n, false));
        for(int i = 0; i < n; ++i) {
            if(transitions[nonterm].contains({word[i]})) {
                dp[nonterm][i][i] = true;
            } else {
                dp[nonterm][i][i] = false;
            }
        }
    }
    for(int delta = 1; delta < n; ++delta) {
        for (int i = 0; i + delta < n; ++i) {
            int j = i + delta;
            for (auto nonterm: nonterminals) {
                for (auto &right_word: transitions[nonterm]) {
                    if (right_word.size() != 2) {
                        continue;
                    }
                    for (int k = i; k < j; ++k) {
                        bool help = (dp[right_word[0]][i][k] && dp[right_word[1]][k + 1][j]);
                        dp[nonterm][i][j] = dp[nonterm][i][j] || help;
                    }
                }
            }
        }
    }
    return dp[start][0][n - 1];
}

void Grammar::to_CNF() {
    first_step_CNF();
    second_step_CNF();
    third_step_CNF();
    fourth_step_CNF();
    fifth_step_CNF();
    sixth_step_CNF();
    seventh_step_CNF();
}

//void Grammar::add_transition(int from, std::set<std::string>& to) {
//    nonterminals.insert(from);
//    std::vector<int> new_right_word;
//    for(auto& word: to) {
//        for(int i = 0; i < word.size(); ++i) {
//            alpabet.insert(word[i]);
//            new_right_word.push_back((int)word[i]);
//        }
//        transitions[from].insert(new_right_word);
//    }
//}

int main() {
    int start = 'S';
    std::map<int, std::set<std::vector<int>>> rules;
    rules['S'] = {{'a', 'F', 'b', 'F'}};
    rules['F'] = {{'a', 'F', 'b'}, {1}, {'G', 'a'}};
    rules['G'] = {{'b', 'S', 'G'}};
    std::set<int> alpabet = {'a', 'b', 1};
    std::set<int> nonterminals = {'S', 'F', 'G'};
    Grammar grammar(start, rules, alpabet, nonterminals);
    grammar.to_CNF();
    std::cout << grammar.in_language("abaabb");
}
