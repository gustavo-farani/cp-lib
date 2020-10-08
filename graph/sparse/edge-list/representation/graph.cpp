#include "../../../../boilerplate.cpp"

struct Edge;

struct Graph {
    int first, last, n;
    vector<Edge*> edges;
    vector<vector<Edge*>> adj;
    // b == 0: vertices indices in range [0, n)
    // b == 1: vertices indices in range [1, n]
    Graph (int n, bool b) :
        first(b), last(n + b), n(n), adj(last)
    {}
    void addEdge (Edge* e) {
        adj[e->from].pb(e);
        adj[e->to].pb(e);
        edges.pb(e);
    }
};