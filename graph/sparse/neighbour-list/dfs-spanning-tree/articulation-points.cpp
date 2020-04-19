#include "../representation/unweighted-graph.cpp"

// g: possibly disconnected and undirected graph
// in neighbour list representation
// return: indices of the vertices in g which are articulation points
// NOTE: cc[u] : in how many pieces vertex u's connected component
// would split if u (and all of its incident edges) were removed
vi articulationPoints (const Graph& g) {
    vi ap, cc(g.last), pre(g.last), low(g.last);
    int cnt = 0;
    function<void(int, int)> dfs = [&] (int u, int par) {
        low[u] = pre[u] = ++cnt;
        for (int v : g.adj[u]) {
            if (pre[v] == 0) {  // tree-edge
                dfs(v, u);
                if (low[v] >= pre[u]) cc[u]++;
                low[u] = min(low[u], low[v]);
            } else if (v == par) {
                cc[u]++;
            } else {            // back-edge or forward-edge
                low[u] = min(low[u], pre[v]);
            }
        }
    };
    for (int u = g.first; u < g.last; u++) {
        if (pre[u] == 0) dfs(u, u);
        if (cc[u] > 1) ap.pb(u);
    }
    return ap;
}