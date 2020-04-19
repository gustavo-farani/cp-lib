#include "../representation/dense-graph.cpp"

template<class T>
T minimumSpanningTree (const DenseGraph<T>& g) {
    T sum = 0; // vector<pair<T, ii>> mst;
    int cnt = 0;
    vector<bool> taken(g.last);
    vi nearest(g.last);
    vector<T> dist(g.last, numeric_limits<T>::max());
    int u = g.first, v;
    while (cnt < g.n - 1) {  // mst.size() < g.n - 1
        taken[u] = true;
        for (v = g.first; v < g.last; v++) {
            if (g.adj[v][u] < dist[v]) {
                dist[v] = g.adj[v][u];
                nearest[v] = u;
            }
        }
        T w = numeric_limits<T>::max();
        for (int i = g.first; i < g.last; i++) {
            if (!taken[i] && dist[i] < w) {
                w = dist[i];
                u = i;
                v = nearest[i];
            }
        }
        sum += w; // mst.pb({w, {u, v}});
        cnt++;
    }
    return sum;  // return mst;
}