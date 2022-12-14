#include "CYK_algorithm.h"

void CYK::CYK_algorithm(const std::string &word) {
    g.to_CNF();
    int n = word.size();
    std::map<int, std::vector<std::vector<bool>>> dp;
    for(auto nonterm: g.nonterminals) {
        dp[nonterm] = std::vector<std::vector<bool>>(n, std::vector<bool>(n, false));
        for(int i = 0; i < n; ++i) {
            if(g.transitions[nonterm].contains({word[i]})) {
                dp[nonterm][i][i] = true;
            } else {
                dp[nonterm][i][i] = false;
            }
        }
    }
    for(int delta = 1; delta < n; ++delta) {
        for (int i = 0; i + delta < n; ++i) {
            int j = i + delta;
            for (auto nonterm: g.nonterminals) {
                for (auto &right_word: g.transitions[nonterm]) {
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
    std::cout << dp[g.start][0][n - 1];
}