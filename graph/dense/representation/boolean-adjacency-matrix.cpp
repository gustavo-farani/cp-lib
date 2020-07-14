#include "../../../template.cpp"

struct Graph {
    int first, last, n;
    vector<vector<bool>> adj;
    Graph (int n, bool b) :
        first(b), last(n + b), n(n), adj(last, vector<bool>(last))
    {}
    void addEdge (int u, int v) { adj[u][v] = adj[v][u] = true; }
    void addArc (int u, int v) { adj[u][v] = true; }
    // transitive-closure.cpp
    vector<vector<bool>> transitiveClosure();
    // strongly-connected-components.cpp
    int stronglyConnectedComponents(vector<vi>& p);
};