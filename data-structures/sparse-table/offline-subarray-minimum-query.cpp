#include "../../template.cpp"

template<class T>
struct RangeMin {
    vector<vector<T>> st;
    vi lg;
    RangeMin (int n) : lg(n + 1) {
        for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
        st.assign(lg[n] + 1, vi(n));
    }
    T& at (int i) { return st[0][i]; } // array must be manually read
    void build (int n) {
        for (int j = 1; j <= lg[n]; j++) for (int i = 0; i + (1 << j) <= n; i++)
            st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }
    T query (int l, int r) {        // 0-based indexation, closed intervals
        int k = lg[r - l + 1];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};