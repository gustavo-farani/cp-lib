#include "../../../../boilerplate.cpp"

struct Graph {  // unweighted graph
    int first, last, n;
    vector<vi> adj;
    // b == 0: vertices indices in range [0, n)
    // b == 1: vertices indices in range [1, n]
    Graph (int n, bool b) :
        first(b), last(n + b), n(n), adj(last)
    {}
    void addEdge (int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);  // for undirected graph
    }
    void addArc (int u, int v) {
        adj[u].pb(v);  // for directed graph
    }
};