#include "../../../../boilerplate.cpp"

struct Graph {
    int first, last, n;
    vector<vector<ii>> adj;
    // base == 0: vertices indices in range [0, n)
    // base == 1: vertices indices in range [1, n]
    Graph (int n, bool b) :
        first(b), last(n + b), n(n), adj(last)
    {}
    void addEdge (int u, int v, int w) {
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);  // for undirected graph
    }
    void addArc (int u, int v, int w) {
        adj[u].emplace_back(w, v);  // for directed graph
    }
};