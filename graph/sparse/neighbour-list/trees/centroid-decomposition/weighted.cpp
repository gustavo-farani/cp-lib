#include "../../representation/weighted-graph.cpp"

// counting paths within some radius around each vertex
struct CentroidDecomposition {
    Graph g;
    vi sz;
    vector<bool> cut;
    CentroidDecomposition (Graph&& g) :  // graph should be moved
        g(g), sz(g.last), cut(g.last)
    {
        solve(g.first, g.first, 0);
    }
    // dfs for computing subtree sizes
    void sizes (int u, int par) {
        sz[u] = 1;
        for (auto [w, v] : g.adj[u]) {
            if (v == par || cut[v]) continue;
            sizes(v, u);
            sz[u] += sz[v];
        }
    }
    // dfs for finding the centroid
    int find (int u, int par, int cnt) {
        for (auto [w, v] : g.adj[u]) {
            if (v == par || cut[v]) continue;
            if (sz[v] << 1 > cnt) return find(v, u, cnt);
        }
        return u;
    }
    // dfs in the subtree rooted at a centroid child
    // searching for half-paths distances
    template<class F>
    void halfPaths (int u, int par, ll d, const F& get) {
        get(u, d);
        for (auto [w, v] : g.adj[u]) {
            if (v == par || cut[v]) continue;
            halfPaths(v, u, d + w, get);
        }
    }
    // solving recursively for an independent tree
    void solve (int c, int par, int h) {
        sizes(c, par);
        c = find(c, par, sz[c]);
        cut[c] = true;
        halfPaths(c, c, 0, [&] (int u, ll d) {
            // increment around u number of semi-paths <= max_len - d
        });
        for (auto [w, r] : g.adj[c]) {
            if (!cut[r]) {
                halfPaths(r, c, w, [&] (int u, ll d) {
                    // decrement around u number of semi-paths <= max_len - d
                });
            }
        }
        for (auto [w, r] : g.adj[c]) {
            if (!cut[r]) solve(r, c, h + 1);
        }
    }
};