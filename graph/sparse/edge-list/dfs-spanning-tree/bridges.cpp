#include "../representation/graph.cpp"

// g: possibly disconnected undirected graph in edge list representation
// pre[u] := pre-order (time of first visit) of node u in dfs
// cnt: visited nodes counter (dfs timer)
// low[u] = min {
//   pre[u],
//   pre[v], for all v such that (u, v) is a back edge
//   low[v], for all v such that (u, v) is a tree edge
// }
// return: indices of the edges in g which are bridges
template<class T>
vi bridges (const Graph<T>& g) {
    vi b, pre(g.last), low(g.last);
    int cnt = 0;
    function<void(int, int)> dfs = [&] (int u, int par) {
        low[u] = pre[u] = ++cnt;
        for (int z : g.adj[u]) {
            int v = u ^ g.e[z].from ^ g.e[z].to;
            if (pre[v] == 0) {  // tree-edge
                dfs(v, u);
                if (low[v] > pre[u]) b.pb(z);  // detected bridge
                low[u] = min(low[u], low[v]);
            } else if (v != par) {
                low[u] = min(low[u], pre[v]);  // back-edge or forward edge
            }
        }
    };
    for (int u = g.first; u < g.last; u++) {
        if (pre[u] == 0) dfs(u, u);
    }
    return b;
}