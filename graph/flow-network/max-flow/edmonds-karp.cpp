#include "../../template.cpp"

struct Edge {
    int to;
    ll cap, flow;
    ll res () { return cap - flow; }
};

struct FlowNetwork {
    vector<vi> adj;
    vector<Edge> e;
    vi hang;
    FlowNetwork (int n, bool b) :  // b: base indexation (0 or 1)
        adj(n + b), hang(n + b)
    {}
    void addArc (int u, int v, int w) {  // directed
        int z = e.size();
        adj[u].pb(z);
        adj[v].pb(z + 1);
        e.pb(Edge{v, w, 0});
        e.pb(Edge{u, 0, 0});
    }
    void addEdge (int u, int v, int w) {  // bidirectional
        int z = e.size();
        adj[u].pb(z);
        adj[v].pb(z + 1);
        e.pb(Edge{v, w, 0});
        e.pb(Edge{u, w, 0});
    }
    void push (int i, ll w) {
        e[i].flow += w, e[i ^ 1].flow -= w;
    }
    ll bfs (int s, int t) {
        fill(hang.begin(), hang.end(), -1);
        queue<pair<ll, int>> q({{LLONG_MAX, s}});
        while (!q.empty()) {
            int u; ll w; tie(w, u) = q.front(); q.pop();
            for (int i : adj[u]) {
                int v = e[i].to;
                if (hang[v] == -1 && e[i].res() > 0) {
                    hang[v] = i;
                    ll neck =  min(w, e[i].res());
                    if (v == t) return neck;
                    else q.emplace(neck, v);
                }
            }
        }
        return 0;
    }
    ll maxFlow (int s, int t) {
        ll sum = 0, w;
        while (w = bfs(s, t)) {
            for (int v = t; v != s; v = e[hang[v] ^ 1].to) push(hang[v], w);
            sum += w;
        }
        return sum;
    }
    // where is vertex u in a minimum cut (S, T)?
    // false: u in S; true: u in T
    bool cut (int u) { return hang[u] == -1; }
};