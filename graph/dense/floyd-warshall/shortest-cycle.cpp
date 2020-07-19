#include "../representation/dense-graph.cpp"

// minimum length of a cycle in the graph
template<class T>
T Graph<T>::girph () {
    auto dist = minimumDistances();
    T ans = numeric_limits<T>::max()/2;
    for (int u = first; u < last; u++) {
        ans = min(ans, dist[u][u]);
    }
    return ans;
}