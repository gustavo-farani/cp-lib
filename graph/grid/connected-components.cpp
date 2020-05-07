#include "../../template.cpp"

// cardinal points: {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}
// intercardinal points: {{1, -1}, {-1, -1}, {-1, 1}, {1, 1}}
vector<ii> windrose({{1, 0}, {0, 1}, {-1, 0}, {0, -1}});
 
struct Grid {
    vector<vi> g, c;
    vi sz;
    Grid (int n, int m) : g(n + 2, vi(m + 2)), c(n + 2, vi(m + 2, -1)) {}
    int& at (int i, int j) { return g[i][j]; }
    void dfs (int ui, int uj, int k) {
        c[ui][uj] = k;
        sz[k]++;
        for (const ii &d : windrose) {
            int vi = ui + d.first, vj = uj + d.second;
            if (g[vi][vj] && c[vi][vj] == -1) dfs(vi, vj, k);
        }
    }
    bool start (int i, int j) {
        if (g[i][j] && c[i][j] == -1) {
            int k = sz.size();
            sz.pb(0);
            dfs(i, j, k);
            return true;
        } else {
            return false;
        }
    }
    int size (int i, int j) {
        if (g[i][j]) {
            if (c[i][j] == -1) {
                int k = sz.size();
                sz.pb(0);
                dfs(i, j, k);
            }
            return sz[c[i][j]];
        } else {
            return 0;
        }
    }
};