#include <vector>
#include "../../data-structures/sparse-table/offline-subarray-minimum-query.cpp"
using namespace std;

#define pb push_back
typedef vector<int> vi;

struct EulerTour {
    vector<vi> adj;
    vi pre, lvl;
    int cnt;
    SparseTable<int> st;
    EulerTour (int n) :
        adj(n + 1), pre(n + 1), lvl(n + 1), // 1-based
        cnt(0), st((n << 1) - 1, [&] (int u, int v) { return lvl[u] <= lvl[v] ? u : v; })
    {}
    void addEdge (int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }
    void dfs (int u, int par) {
        st.at(pre[u] = cnt++) = u;
        for (int v : adj[u]) {
            if (v != par) {
                lvl[v] = lvl[u] + 1;
                dfs(v, u);
                st.at(cnt++) = u;
            }
        }
    }
    void build (int r) { 
        dfs(r, r);
        st.build(cnt);
    }
    int lca (int u, int v) {
        if (pre[u] > pre[v]) swap(u, v);
        return st.query(pre[u], pre[v]);
    }
    int dist (int u, int v) {
        int w = lca(u, v);
        return lvl[u] + lvl[v] - (lvl[w] << 1);
    }
};