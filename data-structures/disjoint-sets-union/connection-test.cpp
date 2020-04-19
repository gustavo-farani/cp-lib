#include <vector>
#include <numeric>
using namespace std;

#define pb push_back
typedef vector<int> vi;

struct DSU {        // union by rank
    vi par, rank;
    DSU (int n) : par(n), rank(n, 0) {  // 0-based
        iota(par.begin(), par.end(), 0);
    }
    int find (int u) {  // representative upon u's connected component
        return par[u] == u ? u : par[u] = find(par[u]);
    }
    bool connected (int u, int v) {  // whether u and v are in the same connected component
        return find(u) == find(v);
    }
    void merge (int u, int v) {    // unify (permanently) two connected components
        u = find(u), v = find(v);
        if (u != v) {
            if (rank[u] < rank[v]) swap(u, v);
            else if (rank[u] == rank[v]) rank[u]++;
            par[v] = u;
        }
    }
};