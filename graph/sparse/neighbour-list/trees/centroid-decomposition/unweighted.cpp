#include "../../representation/unweighted-graph.cpp"

// saving information of the centroid decomposition tree
struct CentroidDecomposition {
    Graph g;
    vi sz, from, lvl;
    vector<bool> cut;
    CentroidDecomposition (Graph&& g) :  // graph should be moved
        g(g), sz(g.last), cut(g.last),
        from(g.last), lvl(g.last)
    {
        solve(g.first, g.first, 0);
    }
    // dfs for computing subtree sizes
    void sizes (int u, int par) {
        sz[u] = 1;
        for (int v : g.adj[u]) {
            if (v == par || cut[v]) continue;
            sizes(v, u);
            sz[u] += sz[v];
        }
    }
    // dfs for finding the centroid
    int find (int u, int par, int cnt) {
        for (int v : g.adj[u]) {
            if (v == par || cut[v]) continue;
            if (sz[v] << 1 > cnt) return find(v, u, cnt);
        }
        return u;
    }
    // solving recursively for an independent tree
    void solve (int c, int par, int h) {
        sizes(c, par);
        c = find(c, par, sz[c]);
        cut[c] = true;
        // setting the centroid-decomposition tree data
        // for the just computed centroid c
        from[c] = par;  // parent node in the centroid-decomposition tree
        lvl[c] = h;  // distance to root in the centroid-decomposition tree
        for (int r : g.adj[c]) {
            if (!cut[r]) solve(r, c, h + 1);
        }
    }
};