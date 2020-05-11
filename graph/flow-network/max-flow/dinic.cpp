#include "../../template.cpp"

struct Edge {
    int to;
    ll cap, flow;
    ll res () { return cap - flow; }
};

struct FlowNetwork {
    vector<vi> adj;
    vector<Edge> e;
    vi dist, cur;
    FlowNetwork (int n, bool b) :  // b: base indexation (0 or 1)
        adj(n + b), dist(n + b), cur(n + b)
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
    bool bfs (int s, int t) {
        fill(dist.begin(), dist.end(), INT_MAX);
        fill(cur.begin(), cur.end(), 0);
        queue<int> q({s});
        dist[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i : adj[u]) {
                int v = e[i].to;
                if (e[i].res() > 0 && dist[u] + 1 < dist[v]) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist[t] < INT_MAX;
    }
    ll dfs (int u, int t, ll neck) {
        if (u == t) {
            return neck;
        } else {
            ll w = 0;
            while (cur[u] < adj[u].size()) {
                int i = adj[u][cur[u]], v = e[i].to;
                if (dist[v] == dist[u] + 1 && e[i].res() > 0) {
                    w = dfs(v, t, min(neck, e[i].res()));
                    if (w > 0) {
                        push(i, w);
                        break;
                    }
                }
                cur[u]++;
            }
            return w;
        }
    }
    ll maxFlow (int s, int t) {
        ll sum = 0;
        while (bfs(s, t)) for (ll w; w = dfs(s, t, LLONG_MAX); sum += w);
        return sum;
    }
    // where is vertex u in a minimum cut (S, T)?
    // false: u in S; true: u in T
    bool cut (int u) { return dist[u] == INT_MAX; }
};