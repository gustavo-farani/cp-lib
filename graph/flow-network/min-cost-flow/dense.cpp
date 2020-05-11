#include "../../../template.cpp"

struct Edge {
    int to;
    ll cap, flow, cost;
    ll res () { return cap - flow; }
};

struct FlowNetwork {
    int first, last;
    vector<Edge> e;
    vector<vi> adj;
    vector<ll> dist, pot, neck;
    vi from;
    vector<bool> taken;
    FlowNetwork (int n, bool base) :  // choose base indexation
        first(base), last(n + base), adj(last), dist(last),
        from(last), pot(last), neck(last), taken(last, true)
    {}
    void addArc (int u, int v, ll cap, ll cost) {  // directed edge
        int z = e.size();
        adj[u].pb(z);
        adj[v].pb(z + 1);
        e.pb(Edge{v, cap, 0, cost});
        e.pb(Edge{u, 0, 0, -cost});
    }
    void spfa (int s) {  // computes initial potential values
        queue<int> q;
        for (int u = first; u < last; u++) q.push(u);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            taken[u] = false;
            for (int i : adj[u]) {
                if (e[i].res() > 0) {
                    int v = e[i].to;
                    if (pot[u] + e[i].cost < pot[v]) {
                        pot[v] = pot[u] + e[i].cost;
                        if (!taken[v]) {
                            q.push(v);
                            taken[v] = true;
                        }
                    }
                }
            }
        }
    }
    bool dijkstra (int s, int t) {  // suitable for dense networks
        fill(dist.begin(), dist.end(), LLONG_MAX);
        fill(from.begin(), from.end(), -1);
        fill(taken.begin(), taken.end(), false);
        fill(neck.begin(), neck.end(), LLONG_MAX);
        dist[s] = 0;
        bool none;
        int u = s;
        do {
            taken[u] = true;
            for (int i : adj[u]) {
                int v = e[i].to;
                ll w = e[i].cost + pot[u] - pot[v];
                if (e[i].res() > 0 && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    from[v] = i;
                    neck[v] = min(neck[u], e[i].res());
                }
            }
            none = true;
            for (int v = first; v < last; v++) {
                if (!taken[v] && from[v] != -1 &&
                (none || dist[v] < dist[u])) {
                    u = v;
                    none = false;
                }
            }
        } while (!none);
        return from[t] != -1;
    }
    ll minCostFlow (int s, int t, ll k) {  // minimum cost flow with value exactly k
        ll value = 0, cost = 0;
        spfa(s);  // only necessary if original graph contains negative-cost edges
        while (value < k && dijkstra(s, t)) {
            ll aug = min(neck[t], k - value);
            for (int v = t; v != s; v = e[from[v] ^ 1].to) {
                cost += e[from[v]].cost*aug;
                e[from[v]].flow += aug;
                e[from[v] ^ 1].flow -= aug;
            }
            value += aug;
            for (int u = first; u < last; u++) {
                if (dist[u] < LLONG_MAX) pot[u] += dist[u];
            }
        }
        if (value < k) throw -1;  // impossible because maximum flow is less than k
        else return cost;
    }
};