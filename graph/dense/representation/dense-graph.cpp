#include "../../../template.cpp"

template<class T>
struct DenseGraph {
    int first, last, n;
    vector<vector<T>> adj;
    // base == 0: vertices indices in range [0, n)
    // base == 1: vertices indices in range [1, n]
    DenseGraph (int n, bool base) :
        first(base), last(n + base), n(n),
        adj(last, vector<T>(n, numeric_limits<T>::max()/2))
    {}
    // addEdge method must be called only once for each unordered pair (u, v)
    void addEdge (int u, int v, T w) {  // no support for multiple edges
        adj[u][v] = adj[v][u] = w;  // for undirected graphs
    }
    void addArc (int u, int v, T w) { adj[u][v] = w; }  // for directed graphs
};