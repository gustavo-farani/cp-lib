#include "../../boilerplate.cpp"

template<class T>
struct SubmatrixSum {
    int n, m;
    vector<vector<T>> bit;
    SubmatrixSum (int n, int m) : n(n), m(m), bit(n + 1, vector<T>(m + 1)) {}
    int lso (int i) { return i & -i; }
    void update (int r, int c, T delta) {
        for (int i = r; i <= n; i += lso(i)) {
            for (int j = c; j <= m; j += lso(j)) {
                bit[i][j] += delta;
            }
        }
    }
    T prefix (int r, int c) {
        T sum = 0;
        for (int i = r; i > 0; i -= lso(i)) {
            for (int j = c; j > 0; j -= lso(j)) {
                sum += bit[i][j];
            }
        }
        return sum;
    }
    T query (int r1, int c1, int r2, int c2) {
        return prefix(r2, c2) + prefix(r1 - 1, c1 - 1)
        - (prefix(r1 - 1, c2) + prefix(r2, c1 - 1));
    }
};