#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
using namespace std;

#define pb push_back
typedef vector<int> vi;
typedef long long ll;

struct FlowNetwork {
    vector<vi> adj;
    vector<vector<ll>> c, f;
    vi p;
    vector<ll> bn;
    FlowNetwork (int n) :   // 0-based
        c(n, vector<ll>(n)), f(c), adj(n), p(n), bn(n)
    {}
    void addEdge (int u, int v, ll w) {
        if (c[u][v] == 0 && c[v][u] == 0) {
            adj[u].pb(v);
            adj[v].pb(u);
        }
        c[u][v] += w;
    }
    bool augmentingPath (int s, int t) {   // Edmonds-Karp BFS
        fill(p.begin(), p.end(), -1);
        p[s] = s;
        bn[s] = numeric_limits<ll>::max();
        bool exists = false;
        queue<int> q({s});
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (p[v] == -1 && c[u][v] > 0) {
                    p[v] = u;
                    bn[v] = min(c[u][v], bn[u]);
                    exists |= (v == t);
                    q.push(v);
                }
            }
        }
        return exists;
    }
    ll maxFlow (int s, int t) {  // Ford-Fulkerson
        ll sum = 0;
        while (augmentingPath(s, t)) {
            ll w = bn[t];
            for (int v = t; v != s; v = p[v]) {
                int u = p[v];
                f[u][v] += w, c[u][v] -= w;
                f[v][u] -= w, c[v][u] += w;
            }
            sum += w;
        }
        return sum;
    }
    ll minCut (int s, vi &a, int t, vi &b, int n) {
        ll ans = maxFlow(s, t);
        for (int i = 0; i < n; i++) {
            if (p[i] == -1) b.pb(i);
            else a.pb(i);
        }
        return ans;   // capacity of the minimum cut
    }
};