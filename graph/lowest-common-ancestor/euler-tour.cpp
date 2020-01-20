#include <algorithm>
#include <vector>
using namespace std;

#define pb push_back
typedef vector<int> vi;

struct LCA {
    int r;
    vector<vi> adj, st;
    vi pre, lvl, euler, lg;
    LCA (int n, int r) :
        adj(n + 1), pre(n + 1), lvl(n + 1), // 1-based
        st((n << 1) - 1), lg(n << 1)  // sparse table: 0-based
    {}
    void addEdge (int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }
    void dfs (int u, int par) {
        pre[u] = euler.size();
        euler.pb(u);
        for (int v : adj[u]) {
            if (v != par) {
                lvl[v] = lvl[u] + 1;
                dfs(v, u);
                euler.pb(u);
            }
        }
    }
    int merge (int u, int v) {
        return (lvl[u] <= lvl[v] ? u : v);
    }
    void build () {
        dfs(r, r);
        int m = euler.size();  // 2*(n - 1) + 1
        for (int i = 2; i <= m; i++) {
            lg[i] = lg[i >> 1] + 1;
        }
        for (int i = 0; i < m; i++) {
            st[i].assign(lg[m - i] + 1, -1);
            st[i][0] = euler[i];
        }
        for (int j = 1; j <= lg[m]; j++) {
            for (int i = 0; i + (1 << j) <= m; i++) {
                st[i][j] = merge(st[i][j - 1],
                st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int query (int l, int r) {
        int k = lg[r - l + 1];
        return merge(st[l][k], st[r - (1 << k) + 1][k]);
    }
    int lca (int u, int v) {
        if (pre[u] > pre[v]) swap(u, v);
        return query(pre[u], pre[v]);
    }
    int dist (int u, int v) {
        int w = lca(u, v);
        return lvl[u] + lvl[v] - (lvl[w] << 1);
    }
};