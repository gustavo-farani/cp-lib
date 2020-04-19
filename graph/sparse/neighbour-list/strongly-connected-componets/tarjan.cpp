#include "../representation/unweighted-graph.cpp"

// g: directed unweighted graph in neighbour list representation
// return: scc[u] := id of the strongly connected component (SCC)
// the vertex with index u is part of
// vertices u, v will lie on the same SCC iff scc[u] == scc[v]
// NOTE: variable id will be storing the number of SCC's in g
// by the moment the algorithm terminates; so you could return id,
// instead of returning scc, for counting how many SCC's in g
vi stronglyConnectedComponents (const Graph& g) {
    int cnt = 0, id = 0;
    vi pre(g.last), low(g.last), scc(g.last);
    vector<bool> on(g.last);
    stack<int> s;
    function<void(int u, int par)> dfs = [&] (int u, int par) {
        low[u] = pre[u] = ++cnt;
        s.push(u);
        on[u] = true;
        for (int v : g.adj[u]) {
            if (pre[v] == 0) dfs(v, u);
            if (on[v]) low[u] = min(low[u], low[v]);
        }
        if (low[u] == pre[u]) {
            id++;
            bool end = false;
            while (!end) {
                int v = s.top();
                scc[v] = id;
                s.pop();
                on[v] = false;
                end = (u == v);
            }
        }
    };
    for (int u = g.first; u < g.last; u++) {
        if (pre[u] == 0) dfs(u, u);
    }
    return scc;
}