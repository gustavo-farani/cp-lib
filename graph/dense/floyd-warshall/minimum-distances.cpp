#include "../representation/dense-graph.cpp"

// dist[u][v]: shortest path distance from u to v
// NOTE: dist[u][u] is initialized as infinite for all vertices u
// you may set dist[u][u] = 0 beforehand, if specified by the problem
template<class T>
vector<vector<T>> Graph<T>::minimumDistances () {
    // remove reference only if necessary to keep original edge weights
    auto& dist = adj;
    for (int mid = first; mid < last; mid++) {
        for (int u = first; u < last; u++) {
            for (int v = first; v < last; v++) {
                dist[u][v] = min(dist[u][v], dist[u][mid] + dist[mid][v]); 
            }
        }
    }
    return dist;
}

// from[u][v]: the last vertex before v on a shortest path from u to v,
// i.e., u -> ... -> from[u][v] -> v
template<class T>
vector<vi> Graph<T>::shortestPaths () {
    // remove reference only if necessary to keep original edge weights
    auto& dist = adj;
    vector<vi> from(first);
    for (int u = first; u < last; u++) from.pb(vi(last, u));
    for (int mid = first; mid < last; mid++) {
        for (int u = first; u < last; u++) {
            for (int v = first; v < last; v++) {
                if (dist[u][mid] + dist[mid][v] < dist[u][v]) {
                    dist[u][v] = dist[u][mid] + dist[mid][v];
                    from[u][v] = from[mid][v];
                }
            }
        }
    }
    return from;
}