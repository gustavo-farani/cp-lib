#include <vector>
using namespace std;

#define pb push_back
typedef vector<int> vi;

struct DSU {
    vi par, sz;
    DSU (int n) : par(1), sz(n + 1, 1) {
        for (int i = 1; i <= n; i++) par.pb(i);
    }
    int find (int u) {
        if (par[u] == u) {
            return u;
        } else {
            return par[u] = find(par[u]);
        }
    }
    void merge (int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            if (sz[u] < sz[v]) swap(u, v);
            par[v] = u;
            sz[u] += sz[v];
        }
    }
    int count (int u) { return sz[find(u)]; }
};