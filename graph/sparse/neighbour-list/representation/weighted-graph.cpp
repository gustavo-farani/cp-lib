#include "../../../../template.cpp"

struct WeightedGraph {
    int first, last, n;
    vector<vector<pair<ll, int>>> adj;
    // base == 0: vertices indices in range [0, n)
    // base == 1: vertices indices in range [1, n]
    WeightedGraph (int n, bool base) :
        first(base), last(n + base), n(n), adj(last)
    {}
    void addEdge (int u, int v, ll w) {
        adj[u].pb({w, v});
        adj[v].pb({w, u});  // for undirected graph
    }
    void addArc (int u, int v, ll w) {
        adj[u].pb({w, v});  // for directed graph
    }
};