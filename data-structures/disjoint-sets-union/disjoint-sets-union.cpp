#include <vector>
using namespace std;

#define pb push_back
typedef vector<int> vi;

struct DSU {
    int n;
    vi par, sz;
    DSU (int n) : n(n), par(1), sz(n + 1, 1) { // 1-based
        for (int i = 1; i <= n; i++) par.pb(i);
    }
    int find (int u) {  // representative upon u's EC
        if (par[u] == u) {
            return u;
        } else {
            return par[u] = find(par[u]);
        }
    }
    void merge (int u, int v) { // unify (permanently) two EC's
        u = find(u);
        v = find(v);
        if (u != v) {
            n--;
            if (sz[u] < sz[v]) swap(u, v);
            par[v] = u;
            sz[u] += sz[v];
        }
    }
    bool tied (int u, int v) {  // whether u and v are in the same EC
        return (find(u) == find(v));
    }
    int count (int u) { return sz[find(u)]; }  // number of members in u's EC
    int size () { return n; }  // number of separate trees in forest
};