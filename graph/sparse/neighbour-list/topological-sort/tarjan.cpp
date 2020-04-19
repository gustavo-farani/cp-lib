#include "../representation/unweighted-graph.cpp"

// g: possibly cyclic directed unweighted graph,
// in neighbour list representation
// return: indices of the vertices in g
// in topological order, if g is DAG
// throws exception if g contains cycle
deque<int> toposort (const Graph& g) {
    deque<int> c(g.last), ts;
    function<void(int)> dfs = [&] (int u) {
        c[u]++;
        for (int v : g.adj[u]) {
            if (c[v] == 0) dfs(v);
            else if (c[v] == 1) throw -1;
        }
        c[u]++;
        ts.push_front(u);
    };
    for (int u = g.first; u < g.last; u++) {
        if (c[u] == 0) dfs(u);
    }
    return ts;
}