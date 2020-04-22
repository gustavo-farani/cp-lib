#include "../../template.cpp"

template<class T>
struct SparseTable2D {
    vector<vector<vector<vector<T>>>> st;
    vi lg;
    function<T(T, T)> merge;
    SparseTable2D (int n, int m, function<T(T, T)> merge) :
        st(n, vector<vector<vector<T>>>(m)),
        lg(1 + max(n, m)), merge(merge)
    {
        for (int i = 2; i < lg.size(); i++) lg[i] = 1 + lg[i >> 1];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                st[i][j].assign(1 + lg[n - i],
                vector<T>(1 + lg[m - j]));
            }
        }
    }
    T& at (int i, int j) {   // 0-based indexation
        return st[i][j][0][0];
    }
    void build (int n, int m) {
        for (int i = 0; i < n; i++) {
            for (int y = 1; y <= lg[m]; y++) {
                for (int j = 0; j + (1 << y) <= m; j++) {
                    st[i][j][0][y] = merge(st[i][j][0][y - 1],
                    st[i][j + (1 << (y - 1))][0][y - 1]);
                }
            }
        }
        for (int j = 0; j < m; j++) {
            for (int x = 1; x <= lg[n]; x++) {
                for (int i = 0; i + (1 << x) <= n; i++) {
                    st[i][j][x][0] = merge(st[i][j][x - 1][0],
                    st[i + (1 << (x - 1))][j][x - 1][0]);
                }
            }
        }
        for (int x = 1; x <= lg[n]; x++) {
            for (int i = 0; i + (1 << x) <= n; i++) {
                for (int y = 1; y <= lg[m]; y++) {
                    for (int j = 0; j + (1 << y) <= m; j++) {
                        st[i][j][x][y] = merge(merge(st[i][j][x - 1][y - 1],
                        st[i][j + (1 << (y - 1))][x - 1][y - 1]),
                        merge(st[i + (1 << (x - 1))][j][x - 1][y - 1],
                        st[i + (1 << (x - 1))][j + (1 << (y - 1))][x - 1][y - 1]));
                    }
                }
            }
        }
    }
    T query (int r1, int c1, int r2, int c2) {  // 0-based indexation, closed intervals
        int x = lg[r2 - r1 + 1];
        int y = lg[c2 - c1 + 1];
        return merge(merge(st[r1][c1][x][y],
        st[r1][c2 - (1 << y) + 1][x][y]),
        merge(st[r2 - (1 << x) + 1][c1][x][y],
        st[r2 - (1 << x) + 1][c2 - (1 << y) + 1][x][y]));
    }
};