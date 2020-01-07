#include <vector>
#include <stack>
#include <algorithm>
#include "../topological-sort/kahn.cpp"   // DAG class
using namespace std;

#define pb push_back
typedef vector<int> vi;
typedef pair<int, int> ii;

struct Digraph {                // directed graph
    int n, cnt;
    vector<vi> adj;
    vi pre, low;
    vector<vi> scc;             // Strongly Connected Components (partition of the vertices set)
    stack<int> s;
    vector<bool> on;
    Digraph (int n) :           // 1-based
        n(n), cnt(0), adj(n + 1),
        pre(n + 1), low(n + 1), on(n + 1)
    {}
    void addEdge (int u, int v) {
        adj[u].pb(v);
    }
    int stronglyConnectedComponents () {
        for (int i = 1; i <= n; i++) {
            if (pre[i] == 0) dfs(i, i);
        }
        return scc.size();
    }
    DAG condensationGraph () {
        int k = stronglyConnectedComponents();
        vi rep(n + 1);
        for (int i = 1; i <= k; i++) {
            for (int u : scc[i - 1]) rep[u] = i;
        }
        vector<ii> edges;
        for (int u = 1; u <= n; u++) {
            for (int v : adj[u]) {
                if (rep[u] != rep[v]) edges.pb({rep[u], rep[v]});
            }
        }
        int m = unique(edges.begin(), edges.end()) - edges.begin();
        DAG c(k);
        for (int i = 0; i < m; i++) {
            c.addEdge(edges[i].first, edges[i].second);
        }
        return c;
    }
    void dfs (int u, int par) {
        low[u] = pre[u] = ++cnt;
        s.push(u);
        on[u] = true;
        for (int v : adj[u]) {
            if (pre[v] == 0) dfs(v, u);
            if (on[v]) low[u] = min(low[u], low[v]);
        }
        if (low[u] == pre[u]) {
            scc.pb(vi());
            bool end = false;
            while (!end) {
                int v = s.top();
                scc.back().pb(v);
                s.pop();
                on[v] = false;
                end = (u == v);
            }
        }
    }
};