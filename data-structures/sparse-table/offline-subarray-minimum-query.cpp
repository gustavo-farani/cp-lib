#include <vector>
#include <functional>
using namespace std;

typedef vector<int> vi;

template<class T>
struct SparseTable {
    vector<vector<T>> st;
    vi lg;
    function<T(T, T)> merge;
    SparseTable (int n, function<T(T, T)> merge) :
        lg(n + 1), merge(merge) 
    {
        for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
        st.assign(lg[n] + 1, vi(n));
    }
    T& at (int i) { return st[0][i]; } // array must be manually read
    void build (int n) {
        for (int j = 1; j <= lg[n]; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = merge(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    T query (int l, int r) {        // 0-based indexation, closed intervals
        int k = lg[r - l + 1];
        return merge(st[k][l], st[k][r - (1 << k) + 1]);
    }
};