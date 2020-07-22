#include "../../boilerplate.cpp"

const int N = 1e5 + 5;
const int MS = N << 5, MSB = 1 << 30;
int z, sz, adj[MS][2], term[MS];

// x: non-negative integer
// inserts number x into the trie
void insert (int x) {
    int cs = 0;
    for (int b = MSB; b; b >>= 1) {
        bool i = x & b;
        if (adj[cs][i] == 0) adj[cs][i] = z++;
        cs = adj[cs][i];
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
        i ^= adj[cs][!i] > 0;
        if (i) ans |= b;
        cs = adj[cs][i];
    }
    t = term[cs];
    return ans;
}

void init () {
    z = 0;
    sz = -1;
    memset(term, 0, sizeof term);
    memset(adj, 0, sizeof adj);
    insert(0);
}