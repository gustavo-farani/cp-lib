#include "../representation/graph.cpp"

struct Edge {
    int from, to;
    bool bridge;
    Edge (int u, int v) : from(u), to(v), bridge(false) {}
    int other (int u) { return u ^ from ^ to; }
};

// g: possibly disconnected undirected graph in edge list representation
// sets e.bridge == true for all edges found to be bridges
void bridges (Graph& g) {
    vi pre(g.last), low(g.last);
    int cnt = 0;
    function<void(int, int)> dfs = [&] (int u, int par) {
        low[u] = pre[u] = ++cnt;
        for (auto e : g.adj[u]) {
            int v = e->other(u);
            if (pre[v] == 0) {  // tree-edge
                dfs(v, u);
                if (low[v] > pre[u]) e->bridge = true;  // detected bridge
                low[u] = min(low[u], low[v]);
            } else if (v != par) {
                low[u] = min(low[u], pre[v]);  // back-edge or forward edge
            }
        }
    };
    for (int u = g.first; u < g.last; u++) {
        if (pre[u] == 0) dfs(u, u);
    }
}