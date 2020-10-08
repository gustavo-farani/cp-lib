#include "../representation/graph.cpp"
#include "../representation/unweighted-edge.cpp"

// g: undirected connected graph in edge list representation
// if g has no bridges, returns true, and modifies the attributes
// (from, to) of g's edges so that they represent a strong orientation
// otherwise returns false: by Robbin's Theorem, there is no strong 
// orientation for graphs containing bridges
bool strongOrientation (Graph& g) {
    vi pre(g.last), low(g.last);
    int cnt = 0;
    bool bridges = false;
    function<void(int, int)> dfs = [&] (int u, int par) {
        low[u] = pre[u] = ++cnt;
        for (auto e : g.adj[u]) {
            int v = e->other(u);
            if (pre[v] == 0) {        // tree-edge
                e->from = u, e->to = v;
                dfs(v, u);
                if (low[v] > pre[u]) bridges = true;  // detected bridge
                low[u] = min(low[u], low[v]);
            } else if (pre[v] < pre[u] && v != par) {
                e->from = u, e->to = v;  // back-edge (not a forward-edge)
                low[u] = min(low[u], pre[v]);
            }
        }
    };
    dfs(g.first, g.first);
    return !bridges;
}