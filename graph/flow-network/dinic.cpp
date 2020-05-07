#include "../../template.cpp"

struct Edge {
    int to;
    ll cap, flow;
    ll res () { return cap - flow; }
};

struct FlowNetwork {
    int first, last;
    vector<vi> adj;
    vector<Edge> e;
    FlowNetwork (int n, bool base) :
        first(base), last(n + base), adj(last)
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
};

ll maxFlow (FlowNetwork& g, int s, int t) {
    vi dist(g.last), cur(g.last);
    auto bfs = [&] () {
        fill(dist.begin(), dist.end(), INT_MAX);
        fill(cur.begin(), cur.end(), 0);
        queue<int> q({s});
        dist[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i : g.adj[u]) {
                int v = g.e[i].to;
                if (g.e[i].res() > 0 && dist[u] + 1 < dist[v]) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist[t] < INT_MAX;
    };
    function<ll(int, ll)> dfs = [&] (int u, ll neck) {
        if (u == t) {
            return neck;
        } else {
            ll w = 0;
            while (cur[u] < g.adj[u].size()) {
                int i = g.adj[u][cur[u]], v = g.e[i].to;
                if (dist[v] == dist[u] + 1 && g.e[i].res() > 0) {
                    w = dfs(v, min(neck, g.e[i].res()));
                    if (w > 0) {
                        g.push(i, w);
                        break;
                    }
                }
                cur[u]++;
            }
            return w;
        }
    };
    ll val = 0;
    while (bfs()) for (ll w; w = dfs(s, LLONG_MAX); val += w);
    return val;
}