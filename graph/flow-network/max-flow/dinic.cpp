#include "../../../template.cpp"

template<class T>
struct FlowNetwork {
    struct Edge {
        int to;
        T cap, flow;
        Edge (int v, T w) : to(v), cap(w), flow(0) {}
        T res () { return cap - flow; }
    };
    vector<vi> adj;
    vector<Edge> e;
    vi dist, cur;
    FlowNetwork (int n, bool b) :  // b: base indexation (0 or 1)
        adj(n + b), dist(n + b), cur(n + b)
    {}
    void addArc (int u, int v, T w) {  // directed
        int z = e.size();
        adj[u].pb(z);
        adj[v].pb(z + 1);
        e.emplace_back(v, w);
        e.emplace_back(u, 0);
    }
    void addEdge (int u, int v, T w) {  // bidirectional
        int z = e.size();
        adj[u].pb(z);
        adj[v].pb(z + 1);
        e.emplace_back(v, w);
        e.emplace_back(u, w);
    }
    void push (int i, T w) {
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
    T dfs (int u, int t, T neck) {
        if (u == t) {
            return neck;
        } else {
            T w = 0;
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
    T maxFlow (int s, int t) {
        T sum = 0;
        while (bfs(s, t)) {
            for (T w; w = dfs(s, t, numeric_limits<T>::max()); sum += w);
        }
        return sum;
    }
    // where is vertex u in a minimum cut (S, T)?
    // false: u in S; true: u in T
    bool cut (int u) { return dist[u] == INT_MAX; }
};