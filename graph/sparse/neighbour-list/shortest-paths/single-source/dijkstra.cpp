#include "../../representation/weighted-graph.cpp"

#include <ext/pb_ds/priority_queue.hpp>
template<class T> using min_heap = __gnu_pbds::priority_queue<T, greater<T>>;

template<class T>
vector<T> minimumDistances (const Graph& g, int s) {
    vector<T> dist(g.last, numeric_limits<T>::max());
    dist[s] = 0;
    min_heap<pair<T, int>> pq;
    vector<typename min_heap<pair<T, int>>::point_iterator> at(g.first);
    for (int v = g.first; v < g.last; v++) at.pb(pq.push({dist[v], v}));
    while (!pq.empty()) {
        auto [l, u] = pq.top(); pq.pop();  // C++ 17 only
        if (l == numeric_limits<T>::max()) break;
        for (auto [w, v] : g.adj[u]) {
            if (l + w < dist[v]) pq.modify(at[v], {dist[v] = l + w, v});
        }
    }
    return dist;
}

// multi-source
template<class T>
vector<T> minimumDistances (const Graph& g, vi& s) {
    vector<T> dist(g.last, numeric_limits<T>::max());
    for (int v : s) dist[v] = 0;
    min_heap<pair<T, int>> pq;
    vector<typename min_heap<pair<T, int>>::point_iterator> at(g.first);
    for (int v = g.first; v < g.last; v++) at.pb(pq.push({dist[v], v}));
    while (!pq.empty()) {
        auto [l, u] = pq.top(); pq.pop();  // C++ 17 only
        if (l == numeric_limits<T>::max()) break;
        for (auto [w, v] : g.adj[u]) {
            if (l + w < dist[v]) pq.modify(at[v], {dist[v] = l + w, v});
        }
    }
    return dist;
}

template<class T>
vi shortestPaths (const Graph& g, int s) {
    vector<T> dist(g.last, numeric_limits<T>::max());
    dist[s] = 0;
    vi from(g.last, -1);
    min_heap<pair<T, int>> pq;
    vector<typename min_heap<pair<T, int>>::point_iterator> at(g.first);
    for (int v = g.first; v < g.last; v++) at.pb(pq.push({dist[v], v}));
    while (!pq.empty()) {
        auto [l, u] = pq.top(); pq.pop();  // C++ 17 only
        if (l == numeric_limits<T>::max()) break;
        for (auto [w, v] : g.adj[u]) {
            if (l + w < dist[v]) {
                pq.modify(at[v], {dist[v] = l + w, v});
                from[v] = u;
            }
        }
    }
    return from;
}