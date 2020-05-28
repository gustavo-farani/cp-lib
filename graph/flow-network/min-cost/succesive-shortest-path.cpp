#include "../../../template.cpp"
#include <ext/pb_ds/priority_queue.hpp>
template<class T> using min_heap = __gnu_pbds::priority_queue<T, greater<T>>;

template<class T>
struct FlowNetwork {
    struct Edge {
        int to;
        T cap, flow, cost;
        T res () { return cap - flow; }
    };
    int first, last;
    vector<Edge> e;
    vector<vi> adj;
    vector<T> dist, pot, neck;
    vi from;
    FlowNetwork (int n, bool base) :
        first(base), last(n + base),
        adj(last), dist(last), pot(last), neck(last), from(last)
    {}
    void addArc (int u, int v, T cap, T cost) {  // directed edge
        int z = e.size();
        adj[u].pb(z);
        adj[v].pb(z + 1);
        e.pb(Edge{v, cap, 0, cost});
        e.pb(Edge{u, 0, 0, -cost});
    }
    void spfa (int s) {  // computes initial potential values
        queue<int> q;
        for (int u = first; u < last; u++) q.push(u);
        vector<bool> taken(last, true);
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
    bool dijkstra (int s, int t) {
        neck[s] = numeric_limits<T>::max();
        min_heap<pair<T, int>> pq;
        vector<typename min_heap<pair<T, int>>::point_iterator> at(first);
        for (int u = first; u < last; u++) {
            dist[u] = u == s ? 0 : numeric_limits<T>::max();
            at.pb(pq.push({dist[u], u}));
        }
        bool reachable = false;
        while (!pq.empty()) {
            int u;
            T l;
            tie(l, u) = pq.top();
            pq.pop();
            if (l == numeric_limits<T>::max()) {
                break;
            } else {
                reachable |= u == t;
                for (int i : adj[u]) {
                    int v = e[i].to;
                    T w = e[i].cost + pot[u] - pot[v];
                    if (e[i].res() > 0 && l + w < dist[v]) {
                        pq.modify(at[v], {dist[v] = l + w, v});
                        from[v] = i;
                        neck[v] = min(neck[u], e[i].res());
                    }
                }
            }
        }
        return reachable;
    }
    T minCostFlow (int s, int t, T k) {  // minimum cost flow with value exactly k
        T value = 0, cost = 0;
        spfa(s);  // only necessary if original graph contains negative-cost edges
        while (value < k && dijkstra(s, t)) {
            T aug = min(neck[t], k - value);
            for (int v = t; v != s; v = e[from[v] ^ 1].to) {
                cost += e[from[v]].cost*aug;
                e[from[v]].flow += aug;
                e[from[v] ^ 1].flow -= aug;
            }
            value += aug;
            for (int u = first; u < last; u++) {
                if (dist[u] < numeric_limits<T>::max()) pot[u] += dist[u];
            }
        }
        if (value < k) throw -1;  // impossible because maximum flow is less than k
        else return cost;
    }
    pair<T, T> minCostMaxFlow (int s, int t) {
        T value = 0, cost = 0;
        spfa(s);  // only necessary if original graph contains negative-cost edges
        while (dijkstra(s, t)) {
            T aug = neck[t];
            for (int v = t; v != s; v = e[from[v] ^ 1].to) {
                cost += e[from[v]].cost*aug;
                e[from[v]].flow += aug;
                e[from[v] ^ 1].flow -= aug;
            }
            value += aug;
            for (int u = first; u < last; u++) {
                if (dist[u] < numeric_limits<T>::max()) pot[u] += dist[u];
            }
        }
        return {value, cost};
    }
};