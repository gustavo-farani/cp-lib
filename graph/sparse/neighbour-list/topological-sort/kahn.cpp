#include "../representation/unweighted-graph.cpp"

// g: possibly cyclic directed graph
// return: indices of the vertices in g
// in topological order, if g is DAG
// throws exception if g contains cycle
vi toposort (const Graph& g) {
    vi deg(g.last);
    for (int u = g.first; u < g.last; u++) {
        for (int v : g.adj[u]) deg[v]++;
    }
    queue<int> q;
    for (int u = g.first; u < g.last; u++) {
        if (deg[u] == 0) q.push(u);
    }
    vi ts;
    while (ts.size() < g.n) {
        if (q.empty()) {
            throw -1;  // cycle found
        } else {
            int u = q.front();
            q.pop();
            ts.pb(u);
            for (int v : g.adj[u]) {
                if (--deg[v] == 0) q.push(v);
            }
        }
    }
    return ts;
}