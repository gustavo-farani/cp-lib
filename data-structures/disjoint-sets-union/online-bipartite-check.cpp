#include "../../boilerplate.cpp"

// B: base indexation
// B == 0: node indices in range [0, n)
// B == 1: node indices in range [1, n]
template<bool B>
struct BipartiteCheck {  // Online Bipartite Graph Check
    vi par, rank;
    vector<bool> ok, c;
    BipartiteCheck (int n) :
        par(n + B), c(n + B), rank(n + B), ok(n + B, true)
    { iota(par.begin(), par.end(), 0); }
    int find (int v) {
        if (par[v] != v) {
            int u = par[v];
            par[v] = find(par[v]);
            c[v] = c[v] ^ c[u];
        }
        return par[v];
    }
    // whether the connected component u is part of is still bipartite
    bool isBicolorable (int u) { return ok[find(u)]; }
    // if the connected component u is part of is still bipartite,
    // returns the right color for vertex u,
    // so that it has no neighbours with the same color
    bool colorOf (int u) {
        find(u);
        return c[u];
    }
    // if u and v are part of the same connected component
    // and it still bipartite, it determines whether
    // adding edge (u, v) would make it no longer bipartite
    bool makesOddCycle (int u, int v) {
        return find(u) == find(v) && !(c[u] ^ c[v]);
    }
    // adding an edge online
    void addEdge (int u, int v) {
        bool oc = true;
        int r = find(u);
        oc = oc ^ c[u];
        u = r;
        r = find(v);
        oc = oc ^ c[v];
        v = r;
        if (u == v) {
            if (oc) ok[u] = false;
        } else {
            if (rank[u] < rank[v]) swap(u, v);
            par[v] = u;
            c[v] = oc;
            ok[u] = ok[u] && ok[v];
            if (rank[u] == rank[v]) rank[u]++;
        }
    }
};