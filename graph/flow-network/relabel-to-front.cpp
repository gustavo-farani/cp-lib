#include "../../template.cpp"

struct FlowNetwork {
    vector<vector<ll>> c, f;
    vector<vi> adj;
    vector<ll> e;
    vi pt, h;
    int n;
    FlowNetwork (int n) :
        c(n, vector<ll>(n)), f(c), adj(n), e(n), pt(n), h(n), n(n)
    {}
    void addEdge (int u, int v, ll w) {
        if (c[u][v] == 0 && c[v][u] == 0) {
            adj[u].pb(v);
            adj[v].pb(u);
        }
        c[u][v] += w;
    }
    void push (int u, int v) {
        ll w = min(e[u], c[u][v]);
        f[u][v] += w, c[u][v] -= w;
        f[v][u] -= w, c[v][u] += w;
        e[u] -= w, e[v] += w;
    }
    void relabel (int u) {
        int m = n << 1;
        for (int v : adj[u]) {
            if (c[u][v] > 0) m = min(m, h[v]);
        }
        h[u] = 1 + m;
    }
    bool discharge (int u) {
        bool up = false;
        while (e[u] > 0) {
            if (pt[u] == adj[u].size()) {
                relabel(u);
                up = true;
                pt[u] = 0;
            } else {
                int v = adj[u][pt[u]];
                if (c[u][v] > 0 && h[u] == h[v] + 1) push(u, v);
                else pt[u]++;
            }
        }
        return up;
    }
    ll maxFlow (int s, int t) {
        for (int v : adj[s]) {
            e[v] = f[s][v] = c[v][s] = c[s][v];
            f[v][s] = -c[s][v];
            c[s][v] = 0;
        }
        h[s] = n;
        list<int> ts;
        for (int u = 0; u < n; u++) {
            if (u != s && u != t) ts.pb(u);
        }
        for (auto it = ts.begin(); it != ts.end(); it++) {
            if (discharge(*it)) {
                ts.splice(ts.begin(), ts, it);
                it = ts.begin();
            }
        }
        return e[t];
    }
};