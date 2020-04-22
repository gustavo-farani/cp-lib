#include "../../representation/weighted-graph.cpp"

vector<ll> minimumDistances (const WeightedGraph& g, int s) {
    vector<ll> dist(g.last, LLONG_MAX);
    min_heap<pair<ll, int>> pq;
    pq.emplace(dist[s] = 0, s);
    while (!pq.empty()) {
        auto [l, u] = pq.top(); pq.pop();  // C++ 17
        if (l <= dist[u]) {
            for (auto [w, v] : g.adj[u]) {  // C++ 17
                if (l + w < dist[v]) {
                    pq.emplace(dist[v] = l + w, v);
                }
            }
        }
    }
    return dist;
}

vi shortestPaths (const WeightedGraph& g, int s) {
    vector<ll> dist(g.last, LLONG_MAX);
    vi from(g.last, -1);
    min_heap<pair<ll, int>> pq;
    pq.emplace(dist[s] = 0, s);
    while (!pq.empty()) {
        auto [l, u] = pq.top(); pq.pop();  // C++ 17
        if (l <= dist[u]) {
            for (auto [w, v] : g.adj[u]) {  // C++ 17
                if (l + w < dist[v]) {
                    from[v] = u;
                    pq.emplace(dist[v] = l + w, v);
                }
            }
        }
    }
    return from;
}