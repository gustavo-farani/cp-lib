#include "../../boilerplate.cpp"

const int N = 1e5 + 5;
const int MS = N << 5, MSB = 1 << 30;
int z, sz, dfa[MS][2], term[MS];

// x: non-negative integer
// inserts number x into the trie
void insert (int x) {
    int cs = 0;
    for (int b = MSB; b; b >>= 1) {
        bool i = x & b;
        if (dfa[cs][i] == 0) dfa[cs][i] = z++;
        cs = dfa[cs][i];
    }
    // the number inserted later overrides its predecessor (if any)
    // the timer is 1-based
    term[cs] = ++sz;
}

// x: non-negative integer
// ans: number in trie such that x ^ ans is maximum
// t: is assigned the latest time when number ans was inserted
int maxXor (int x, int &t) {
    int ans = 0, cs = 0;
    for (int b = MSB; b; b >>= 1) {
        bool i = x & b;
        i ^= dfa[cs][!i] > 0;
        if (i) ans |= b;
        cs = dfa[cs][i];
    }
    t = term[cs];
    return ans;
}

void init () {
    z = 0;
    sz = -1;
    memset(term, 0, sizeof term);
    memset(dfa, 0, sizeof dfa);
    insert(0);
}