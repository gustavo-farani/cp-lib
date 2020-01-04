#include <vector>
using namespace std;

#define pb push_back
typedef vector<int> vi;

struct Graph {          // cut-vertices in an undirected and possibly disconnected graph
    int n;
    vector<vi> adj;     // unweighted adjacency list
    vi pre;             // pre-order (time of first visit) of a node in dfs
    int cnt;            // visited nodes counter
    vi low;             // trick for finding cut-vertices efficiently
    /* low[u] = min {
        pre[u],
        pre[v], for all v such that (u, v) is a back edge
        low[v], for all v such that (u, v) is a tree edge
    } */
    vi cc;              /* cc[u] : in how many pieces vertex u's connected
    component would split if u (and all of its incident edges) were removed */
    Graph (int n) :     // 1-based
        n(n), adj(n + 1), pre(n + 1),
        cnt(0), low(n + 1), cc(n + 1)
    {}
    void addEdge (int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vi cutVertices () {
        vi cv;
        for (int i = 1; i <= n; i++) {
            if (pre[i] == 0) dfs(i, i);
            if (cc[i] > 1) {
                cv.pb(i);          // u is cut-vertex iff cc[u] > 1
            }
        }
        return cv;
    }
    void dfs (int u, int par) {
        low[u] = pre[u] = ++cnt;
        for (int v : adj[u]) {
            if (pre[v] == 0) {    // tree-edge
                dfs(v, u);
                if (low[v] >= pre[u]) cc[u]++;
                low[u] = min(low[u], low[v]);
            } else if (v == par) {
                cc[u]++;
            } else {              // back-edge or forward-edge
                low[u] = min(low[u], pre[v]);
            }
        }
    }
};