// useful for Longest Increasing Subsequence problems
template<class T>
struct PrefixMax {
    int n;
    vector<T> bit;
    PrefixMax (int n) : n(n), bit(n + 1) {}  // 1-based
    int lso (int j) { return j & -j; }
    // assumes new value x is never less than the old value at position i
    void update (int i, const T& x) {
        for (int j = i; j <= n; j += lso(j)) bit[j] = max(bit[j], x);
    }
    T prefix (int i) {
        T ans = T();
        for (int j = i; j > 0; j -= lso(j)) ans = max(ans, bit[j]);
        return ans;
    }
};