#include "../../boilerplate.cpp"

// Offline implementation of a multiset
// with order statistics queries
// using a simple binary indexed tree
struct OrderStatistics {
    int n, MSB;
    vi bit;
    OrderStatistics (int n) :  // keys will be in range [0, n)
        bit(n + 1), n(n),
        MSB(1 << (31 - __builtin_clz(n)))
    {}
    int lso (int i) { return i & -i; }
    // insertion of the key with index i (0-based)
    // complexity: O(lg n)
    void insert (int i) {
        for (int j = i + 1; j <= n; j += lso(j)) bit[j]++;
    }
    // deletion of the key with index i (0-based)
    // complexity: O(lg n)
    void remove (int i) {
        for (int j = i + 1; j <= n; j += lso(j)) bit[j]--;
    }
    // counts the number of elements in the set
    // with index smaller than i (0-based)
    // complexity: O(lg n)
    int orderOfKey (int i) {
        int cnt = 0;
        for (int j = i; j > 0; j -= lso(j)) cnt += bit[j];
        return cnt;
    }
    // counts the number of elements in the set with index i (0-based)
    // complexity: O(lg n) - optimized!
    int count (int i) {
        int cnt = bit[++i];
        for (int j = i - 1; j > i - lso(i); j -= lso(j)) cnt -= bit[j];
        return cnt;
    }
    // index (0-based) of the key standing in the
    // k-th (0-based) smallest position in the set
    // if k >= total of elements in the set, it returns n
    // complexity: O(lg n) - it's not O(lg^2 n)!
    // --- OLD COMMENT ---
    // return: rightmost i for which prefix(i) < k
    // assumes prefix(i) increases monotonically, i.e.,
    // at(i) >= 0, for all i
    // NOTE: for the corner case when prefix(1) >= x, it returns 0
    int findByOrder (int k) {
        int i = 0;
        for (int b = MSB; b; b >>= 1) {
            int j = i | b;
            if (j <= n && k > bit[j]) k -= bit[i = j];
        }
        return i;
    }
};