#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

#define pb push_back
typedef long long ll;
typedef pair<ll, int> Edge;
typedef vector<int> vi;

const ll INF = 1e18;

struct Graph {     // Dijkstra's Algorithm
    int n;
    vector< vector<Edge> > adj;  // weighted graph
    Graph (int n) : n(n), adj(n) {}   // 0-based
    void addEdge (int u, int v, int w) {
        adj[u].pb({w, v});    // undirected graph
        adj[v].pb({w, u});
    }
    vector<ll> minimumDistances (int src) {
        vector<ll> dist(n, INF);
        priority_queue< Edge, vector<Edge>, greater<Edge> > margin;
        margin.emplace(dist[src] = 0, src);
        while (!margin.empty()) {
            int u;
            ll l;
            tie (l, u) = margin.top();
            margin.pop();
            if (l <= dist[u]) {
                for (Edge e : adj[u]) {
                    int v, w;
                    tie (w, v) = e;
                    if (l + w < dist[v]) {
                        margin.emplace(dist[v] = l + w, v);
                    }
                }
            }
        }
        return dist;
    }
    vi shortestPaths (int src) {
        vector<ll> dist(n, INF);
        vi from(n);
        priority_queue< Edge, vector<Edge>, greater<Edge> > margin;
        margin.emplace(dist[src] = 0, src);
        while (!margin.empty()) {
            int u;
            ll l;
            tie (l, u) = margin.top();
            margin.pop();
            if (l <= dist[u]) {
                for (Edge e : adj[u]) {
                    int v, w;
                    tie (w, v) = e;
                    if (l + w < dist[v]) {
                        from[v] = u;
                        margin.emplace(dist[v] = l + w, v);
                    }
                }
            }
        }
        return from;
    }
};