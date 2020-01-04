#include <vector>
#include <tuple>
using namespace std;

#define pb push_back
typedef vector<int> vi;
typedef pair<int, int> ii;

struct Graph {          // bridges in an undirected and possibly disconnected graph
    int n;
    vector<vi> adj;     // unweighted adjacency list
    vi pre;             // pre-order (time of first visit) of a node in dfs
    int cnt;            // visited nodes counter
    vi low;             // trick for finding bridges efficiently
    /* low[u] = min {
        pre[u],
        pre[v], for all v such that (u, v) is a back edge
        low[v], for all v such that (u, v) is a tree edge
    } */
    vector<ii> b;       // list of decteded bridges
    Graph (int n) :     // 1-based
        n(n), adj(n + 1), pre(n + 1),
        cnt(0), low(n + 1)
    {}
    void addEdge (int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<ii> bridges () {
        for (int i = 1; i <= n; i++) {
            if (pre[i] == 0) dfs(i, i);
        }
        return b;
    }
    void dfs (int u, int par) {
        low[u] = pre[u] = ++cnt;
        for (int v : adj[u]) {
            if (pre[v] == 0) {               // tree-edge
                dfs(v, u);
                if (low[v] > pre[u]) {
                    b.pb({u, v});            // detected bridge
                }
                low[u] = min(low[u], low[v]);
            } else if (v != par) {           // back-edge or forward edge
                low[u] = min(low[u], pre[v]);
            }
        }
    }
};