#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
using namespace std;

#define pb push_back
typedef vector<int> vi;
typedef long long ll;

const ll INF = 1e18;

struct FlowNetwork {
    vector<vi> adj;
    vector< vector<ll> > res/*, flow*/;
    vi pred;
    vector<ll> neck;
    FlowNetwork (int n) :   // 0-based
        res(n, vector<ll>(n)),
        // flow(n, vector<ll>(n)),
        adj(n), pred(n), neck(n)
    {}
    // calling addEdge(u, v, w) and addEdge(v, u, w) for undirected edge
    // won't throw an error; multiple edges are also accepted
    void addEdge (int u, int v, ll w) {
        if (res[u][v] == 0 && res[v][u] == 0) {
            adj[u].pb(v);
            adj[v].pb(u);
        }
        res[u][v] += w;
    }
    bool augmentingPath (int s, int t) {   // Edmonds-Karp BFS
        bool exists = false;
        fill(pred.begin(), pred.end(), -1);
        queue<int> q;
        pred[s] = s;
        neck[s] = INF;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (pred[v] == -1 && res[u][v] > 0) {
                    pred[v] = u;
                    neck[v] = min(res[u][v], neck[u]);
                    exists |= (v == t);
                    q.push(v);
                }
            }
        }
        return exists;
    }
    ll maximumFlow (int s, int t) {  // Ford-Fulkerson
        ll sum = 0;
        while (augmentingPath(s, t)) {
            ll c = neck[t];
            for (int v = t; v != s; v = pred[v]) {
                int u = pred[v];
                // flow[u][v] += c;
                // flow[v][u] -= c;
                res[u][v] -= c;
                res[v][u] += c;
            }
            sum += c;
        }
        return sum;
    }
    ll minimumCut (int s, vi &a, int t, vi &b, int n) {
        ll ans = maximumFlow(s, t);
        for (int i = 0; i < n; i++) {
            if (pred[i] == -1) {
                b.pb(i);
            } else {
                a.pb(i);
            }
        }
        return ans;   // capacity of the minimum cut
    }
};