#include "../../template.cpp"

// !TODO set the alphabet size
const int SIGMA = 'z' - 'a' + 1;

// !TODO define 0-based ordinal position for each character
int getID (char ch) { return ch - 'a'; }

struct PalindromeTree {
    struct Node {
        int len, suff;
        array<int, SIGMA> adj;
        Node (int len) : len(len) { adj.fill(-1); }
        int& operator[] (char ch) { return adj[getID(ch)]; }
    };
    vector<Node> trie;
    PalindromeTree (const string& s) : trie({Node(0), Node(-1)}) {
        trie[0].suff = trie[1].suff = 1;
        int last = 1;
        for (int i = 0; i < s.length(); i++) {
            int cur = last;
            while (s[i - trie[cur].len - 1] != s[i]) {
                cur = trie[cur].suff;
            }
            int now;
            if (trie[cur][s[i]] == -1) {
                now = trie[cur][s[i]] = trie.size();
                trie.emplace_back(trie[cur].len + 2);
                int deep = trie[now].suff;
                while (s[i - trie[deep].len - 1] != s[i]) {
                    deep = trie[deep].suff;
                }
                trie[now].suff = cur == deep ? 0 : trie[deep][s[i]];
            } else {
                now = trie[cur][s[i]];
            }
            last = trie[now].len == i + 1 ? trie[now].suff : now;
        }
    }
    // number of DISTINCT palindromic substrings
    int size () { return trie.size() - 2; }
};