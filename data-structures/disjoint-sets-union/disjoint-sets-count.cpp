#include <vector>
#include <numeric>
using namespace std;

#define pb push_back
typedef vector<int> vi;

struct DSU {         // union by size
    int n;           // number of separate trees (disjoint sets) in forest
    vi par, sz;
    DSU (int n) : n(n), par(1), sz(n + 1, 1) { // 1-based
        for (int i = 1; i <= n; i++) par.pb(i);
    }
    int find (int u) {  // representative upon u's connected component
        if (par[u] == u) {
            return u;
        } else {
            return par[u] = find(par[u]);
        }
    }
    bool connected (int u, int v) {  // whether u and v are in the same connected component
        return (find(u) == find(v));
    }
    int count (int u) { return sz[find(u)]; }   // number of members among u's connected component
    void merge (int u, int v) {    // unify (permanently) two connected components
        u = find(u);
        v = find(v);
        if (u != v) {
            n--;
            if (sz[u] < sz[v]) swap(u, v);
            par[v] = u;
            sz[u] += sz[v];
        }
    }
};