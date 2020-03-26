#include <vector>
#include <numeric>
using namespace std;

#define pb push_back
typedef vector<int> vi;

struct DSU {       // union by size
    vi par, sz;
    DSU (int n) : par(n + 1), sz(n + 1, 1) {    // 1-based indexation
        iota(par.begin(), par.end(), 0);
    }
    int find (int u) {  // representative upon u's connected component
        return par[u] == u ? u : par[u] = find(par[u]);
    }
    bool connected (int u, int v) {  // whether u and v are in the same connected component
        return find(u) == find(v))
    }
    void merge (int u, int v) {     // unify (permanently) two connected components
        u = find(u); v = find(v);
        if (u != v) {
            if (sz[u] < sz[v]) swap(u, v);
            par[v] = u;
            sz[u] += sz[v];
        }
    }
    int count (int u) { return sz[find(u)]; }  // number of members among u's connected component
};