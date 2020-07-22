#include "../../../../boilerplate.cpp"

struct Graph {  // unweighted graph
    int first, last, n;
    vector<vi> adj;
    // base == 0: vertices indices in range [0, n)
    // base == 1: vertices indices in range [1, n]
    Graph (int n, bool base) :
        first(base), last(n + base), n(n), adj(last)
    {}
    void addEdge (int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);  // for undirected graph
    }
    void addArc (int u, int v) {
        adj[u].pb(v);  // for directed graph
    }
};