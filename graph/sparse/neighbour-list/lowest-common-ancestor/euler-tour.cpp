#include "../../data-structures/sparse-table/offline-subarray-minimum-query.cpp"
#include "../representation/unweighted-graph.cpp"

struct EulerTour {
    vi pre, lvl;
    SparseTable<int> st;
    EulerTour (const Graph& g) :
        pre(g.last), lvl(g.last), st((g.n << 1) - 1,
        [&] (int u, int v) { return lvl[u] <= lvl[v] ? u : v; })
    {  // g: unweighted tree in neighbour list representation
        int cnt = 0;
        function<void(int u, int par)> dfs = [&] (int u, int par) {
            st.at(pre[u] = cnt++) = u;
            for (int v : g.adj[u]) {
                if (v != par) {
                    lvl[v] = lvl[u] + 1;
                    dfs(v, u);
                    st.at(cnt++) = u;
                }
            }
        };
        dfs(g.first, g.first);
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