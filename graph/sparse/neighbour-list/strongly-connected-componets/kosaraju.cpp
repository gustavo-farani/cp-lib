#include "../representation/unweighted-graph.cpp"

// g: directed unweighted graph in neighbour list representation
// return: scc[u] := id of the strongly connected component (SCC)
// the vertex in g with index u is part of
// vertices u, v will lie on the same SCC iff scc[u] == scc[v]
// NOTE: the scc ids follow a topological ordering in g's
// condensation graph, so for v to be reachable from u in g,
// it is necessary, but not sufficient, that scc[u] <= scc[v]
// NOTE: variable cnt will be storing the number of SCC's in g
// by the moment the algorithm terminates; so you could return cnt,
// instead of returning scc, for just counting how many SCC's are in g
vi stronglyConnectedComponents (const Graph& g) {
    Graph t(g.n, g.first);  // build the transposed graph
    for (int u = g.first; u < g.last; u++) {
        for (int v : g.adj[u]) t.addArc(v, u);
    }
    vector<bool> mark(g.last);
    deque<int> ts;
    function<void(int)> topo = [&] (int u) {
        mark[u] = true;
        for (int v : t.adj[u]) {
            if (!mark[v]) topo(v);
        }
        ts.push_front(u);
    };
    for (int u = g.first; u < g.last; u++) {
        if (!mark[u]) topo(u);
    }
    int cnt = 0;
    vi scc(g.last);
    function<void(int, int)> flood = [&] (int u, int label) {
        scc[u] = label;
        mark[u] = false;
        for (int v : g.adj[u]) {
            if (mark[v]) flood(v, label);
        }
    };
    for (int u : ts) {
        if (mark[u]) flood(u, cnt++);
    }
    return scc;
}