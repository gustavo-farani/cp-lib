#include <vector>
#include <tuple>
using namespace std;

#define pb push_back
typedef vector<int> vi;
typedef pair<int, int> ii;

struct Graph {           // strong orientation in an undirected connected graph
    vector<vi> adj;      // unweighted adjacency list
    vi pre;              // pre-order (time of first visit) of a node in dfs
    int cnt;             // visited nodes counter
    vi low;              // trick for finding bridges efficiently
    /* low[u] = min {
        pre[u],
        pre[v], for all v such that (u, v) is a back edge
        low[v], for all v such that (u, v) is a tree edge
    } */
    int r;               // root for dfs spanning tree
    vector<ii> edges;    // edge list of the resulting directed graph
    Graph (int n) :      // 1-based
        adj(n + 1), pre(n + 1),
        cnt(0), low(n + 1), r(1)
    {}
    void addEdge (int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }
    void findStrongOrientation () {
        dfs(r, r);
    }
    void dfs (int u, int par) {
        low[u] = pre[u] = ++cnt;
        for (int v : adj[u]) {
            if (pre[v] == 0) {        // tree-edge
                edges.pb({u, v});
                dfs(v, u);
                if (low[v] > pre[u]) {
                    throw -1;         // edge (u, v) detected as bridge
                    /* by Robbin's Theorem, there is no strong 
                    orientation for graphs containing bridges */
                }
                low[u] = min(low[u], low[v]);
            } else if (pre[v] < pre[u] && v != par) {
                edges.pb({u, v});    // back-edge (not a forward-edge)
                low[u] = min(low[u], pre[v]);
            }
        }
    }
};