#include "../../../template.cpp"

template<class T>
struct Graph {
    int first, last, n;
    vector<vector<T>> adj;
    // b == 0: vertices indices in range [0, n)
    // b == 1: vertices indices in range [1, n]
    Graph (int n, bool b) :
        first(b), last(n + b), n(n),
        adj(last, vector<T>(last, numeric_limits<T>::max()/2))
    {}
    // for undirected graphs without multiple edges
    void addEdge (int u, int v, T w) { adj[u][v] = adj[v][u] = w; }
    // for directed graphs with multiple edges
    void addArc (int u, int v, T w) { adj[u][v] = w; }
    // minimum-spanning-tree/prim.cpp
    T minimumSpanningTree();
    // floyd-warshall/minimum-distances.cpp
    vector<vector<T>> minimumDistances();
    vector<vi> shortestPaths();
    // floyd-warshall/relaxation-dp.cpp
    vector<vector<vector<T>>> relaxation(const vi& p);
    // floyd-warshall/minimax.cpp
    vector<vector<T>> minimax();
    // floyd-warshall/negative-cycle-test.cpp
    bool hasNegativeCycle();
    // floyd-warshall/shortest-cycle.cpp
    T girph();
};