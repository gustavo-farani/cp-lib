#include "../../representation/weighted-graph.cpp"
#include <ext/pb_ds/priority_queue.hpp>
template<class T> using min_heap = __gnu_pbds::priority_queue<T, greater<T>>;

template<class T>
vector<T> minimumDistances (const WeightedGraph& g, int s) {
    vector<T> dist(g.last, numeric_limits<T>::max());
    min_heap<pair<T, int>> pq;
    vector<typename min_heap<pair<T, int>>::point_iterator> at(g.first);
    for (int v = g.first; v < g.last; v++) {
        pair<T, int> e;
        dist[v] = e.first = v == s ? 0 : numeric_limits<T>::max();
        e.second = v;
        at.pb(pq.push(e));
    }
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
vi shortestPaths (const WeightedGraph& g, int s) {
    vector<T> dist(g.last, numeric_limits<T>::max());
    vi from(g.last, -1);
    min_heap<pair<T, int>> pq;
    vector<typename min_heap<pair<T, int>>::point_iterator> at(g.first);
    for (int v = g.first; v < g.last; v++) {
        pair<T, int> e;
        dist[v] = e.first = v == s ? 0 : numeric_limits<T>::max();
        e.second = v;
        at.pb(pq.push(e));
    }
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