#include "../../boilerplate.cpp"

template<class T>
struct RangeSum {   // Binary Indexed Tree for Online Range Sum Query
    int n;
    vector<T> bit;
    RangeSum (int n = 0) : bit(n + 1), n(n) {}
    int lso (int i) { return i & -i; }
    void update (int i, T delta) {   // 1-based
        for (int j = i; j <= n; j += lso(j)) bit[j] += delta;
    }
    T prefix (int i) {               // 1-based
        T sum = 0;
        for (int j = i; j > 0; j -= lso(j)) sum += bit[j];
        return sum;
    }
    T query (int l, int r) { return prefix(r) - prefix(l - 1); }
    void pb (T x) {  // augments the BIT iteratively
        bit.pb(x);
        n++;
        bit.back() += query(n - lso(n) + 1, n - 1);
    }
};