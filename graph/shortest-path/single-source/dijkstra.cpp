#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include "../../default/graph.cpp"
using namespace std;

#define pb push_back
typedef long long ll;
typedef vector<int> vi;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

const ll INF = 1e18;

template<class T>
vector<ll> Graph<T>::minimumDistances (int s) {
    vector<ll> dist(n + 1, INF);     // 1-based indexation
    min_heap<pair<ll, int>> pq;
    pq.emplace(dist[s] = 0, s);
    while (!pq.empty()) {
        int u; ll l;
        tie (l, u) = pq.top(); pq.pop();
        // simply auto [l, u] = pq.top(); pq.pop(); for C++ 17
        if (l <= dist[u]) {
            for (int z : adj[u]) {
                int v = u ^ edges[z].from ^ edges[z].to;
                ll w = edges[z].weigth;
                if (l + w < dist[v]) {
                    pq.emplace(dist[v] = l + w, v);
                }
            }
        }
    }
    return dist;
}

template<class T>
vi Graph<T>::shortestPaths (int s) {
    vector<ll> dist(n + 1, INF);    // 1-based
    vi from(n + 1);                 // 1-based
    min_heap<pair<ll, int>> pq;
    pq.emplace(dist[s] = 0, s);
    while (!pq.empty()) {
        int u; ll l;
        tie (l, u) = pq.top(); pq.pop();
        /* simply auto [l, u] = pq.top(); pq.pop(); for C++ 17 */
        if (l <= dist[u]) {
            for (int z : adj[u]) {
                int v = u ^ edges[z].from ^ edges[z].to;
                ll w = edges[z].weigth;
                if (l + w < dist[v]) {
                    from[v] = u;
                    pq.emplace(dist[v] = l + w, v);
                }
            }
        }
    }
    return from;
}