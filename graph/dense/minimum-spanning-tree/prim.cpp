#include "../representation/dense-graph.cpp"

template<class T>
T Graph<T>::minimumSpanningTree () {
    T sum = 0; // vector<pair<T, ii>> mst;
    int cnt = 0;
    vector<bool> taken(last);
    vi nearest(last);
    vector<T> dist(last, numeric_limits<T>::max()/2);
    int u = first, v;
    while (cnt < n - 1) {  // mst.size() < n - 1
        taken[u] = true;
        for (v = first; v < last; v++) {
            if (adj[v][u] < dist[v]) {
                dist[v] = adj[v][u];
                nearest[v] = u;
            }
        }
        T w = numeric_limits<T>::max()/2;
        for (int i = first; i < last; i++) {
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