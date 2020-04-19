#include "../representation/graph.cpp"

// g: undirected connected graph in edge list representation
// pre[u] := pre-order (time of first visit) of node u in dfs
// cnt: visited nodes counter (dfs timer)
// low[u] = min {
//   pre[u],
//   pre[v], for all v such that (u, v) is a back edge
//   low[v], for all v such that (u, v) is a tree edge
// }
// if g has no bridges, returns true, and modifies the attributes
// (from, to) of g's edges so that they represent a strong orientation
// otherwise returns false: by Robbin's Theorem, there is no strong 
// orientation for graphs containing bridges
template<class T>
bool strongOrientation (Graph<T>& g) {
    vi pre(g.last), low(g.last);
    int cnt = 0;
    bool bridges = false;
    function<void(int, int)> dfs = [&] (int u, int par) {
        low[u] = pre[u] = ++cnt;
        for (int z : g.adj[u]) {
            int v = u ^ g.e[z].from ^ g.e[z].to;
            if (pre[v] == 0) {        // tree-edge
                g.e[z].from = u, g.e[z].to = v;
                dfs(v, u);
                if (low[v] > pre[u]) bridges = true;  // detected bridge
                low[u] = min(low[u], low[v]);
            } else if (pre[v] < pre[u] && v != par) {
                g.e[z].from = u, g.e[z].to = v;  // back-edge (not a forward-edge)
                low[u] = min(low[u], pre[v]);
            }
        }
    };
    dfs(g.first, g.first);
    return !bridges;
}