#include <vector>
#include <deque>
#include <algorithm>
#include "../topological-sort/kahn.cpp"   // DAG class
using namespace std;

#define pb push_back
typedef vector<int> vi;
typedef pair<int, int> ii;

struct Digraph {
    int n;
    vector<vi> in, out, scc;
    vector<bool> vis;
    deque<int> ts;
    Digraph (int n) :      // 1-based
        n(n), in(n + 1),
        out(n + 1), vis(n + 1)
    {}
    void addEdge (int u, int v) {
        out[u].pb(v);
        in[v].pb(u);
    }
    void post (int u) {
        vis[u] = true;
        for (int v : out[u]) {
            if (!vis[v]) post(v);
        }
        ts.push_front(u);
    }
    void pre (int u) {
        vis[u] = false;
        scc.back().pb(u);
        for (int v : in[u]) {
            if (vis[v]) pre(v);
        }
    }
    vector<vi>& stronglyConnectedComponents () {
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) post(i);
        }
        for (int u : ts) {
            if (vis[u]) {
                scc.pb(vi());
                pre(u);
            }
        }
        return scc;
    }
    DAG condensationGraph () {
        stronglyConnectedComponents();
        vi rep(n + 1);
        for (int i = 1; i <= scc.size(); i++) {
            for (int u : scc[i - 1]) rep[u] = i;
        }
        vector<ii> edges;
        for (int u = 1; u <= n; u++) {
            for (int v : out[u]) {
                if (rep[u] != rep[v]) edges.pb({rep[u], rep[v]});
            }
        }
        int m = unique(edges.begin(), edges.end()) - edges.begin();
        DAG c(scc.size());
        while (m--) c.addEdge(edges[m].first, edges[m].second);
        return c;
    }
};