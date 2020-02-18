#include <vector>
using namespace std;
    
#define pb push_back
typedef vector<int> vi;
    
struct BinaryLifting {
    vector<vi> adj, up;
    vi lvl;
    BinaryLifting (int n) :
        adj(n + 1), up(n + 1), 
        lvl(n + 1)
    {}
    void addEdge (int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }
    void dfs (int u, int par) {
        for (int v : adj[u]) {
            if (v != par) {
                lvl[v] = 1 + lvl[u];
                up[v].pb(u);
                for (int i = 0, a = u; i < up[a].size(); a = up[a][i++]) {
                    up[v].pb(up[a][i]);
                }
                dfs(v, u);
            }
        }
    }
    void build (int r) { dfs(r, r); }
    int lift (int u, int k) {
        for (int i = 0; k; i++) {
            if (k & 1) u = up[u][i];
            k >>= 1;
        }
        return u;
    }
    int lca (int u, int v) {
        if (lvl[u] < lvl[v]) swap(u, v);
        u = lift(u, lvl[u] - lvl[v]);
        if (u == v) {
            return u;
        } else {
            for (int i = up[u].size() - 1; i >= 0; i--) {
                if (i < up[u].size() && up[u][i] != up[v][i]) {
                    u = up[u][i];
                    v = up[v][i];
                }
            }
            return up[u][0];
        }
    }
    int dist (int u, int v) {
        int w = lca(u, v);
        return lvl[u] + lvl[v] - (lvl[w] << 1);
    }
};