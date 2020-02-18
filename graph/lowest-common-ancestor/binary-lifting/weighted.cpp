#include <vector>
#include <tuple>
using namespace std;

#define pb push_back
typedef vector<int> vi;
typedef pair<int, int> ii;

// stores information about the edges along the path between two vertices in the tree
struct Path {                 // Ex: sum of edge weights, maximum/mininum edge weight
    Path operator+ (const Path& o);
    void operator+= (const Path& o) { *this = *this + o; }
} NIL;

struct BinaryLifting {
    vector< vector<ii> > adj;    // weighted adjacency list
    vector<vi> up;               // ancestry matrix
    vector< vector<Path> > qr;   // auxiliar matrix
    vi lvl;
    BinaryLifting (int n) :
        adj(n + 1), up(n + 1),
        lvl(n + 1), qr(n + 1)
    {}
    void addEdge (int u, int v, int w) {
        adj[u].pb({w, v});
        adj[v].pb({w, u});
    }
    void dfs (int u, int par) {
        for (ii &e : adj[u]) {
            int v, w;
            tie (w, v) = e;
            if (v != par) {
                lvl[v] = 1 + lvl[u];
                up[v].pb(u);
                qr[v].pb(Path{w});
                for (int i = 0, a = u; i < up[a].size(); a = up[a][i++]) {
                    up[v].pb(up[a][i]);
                    qr[v].pb(qr[v][i] + qr[a][i]);
                }
                dfs(v, u);
            }
        }
    }
    void build (int r) { dfs(r, r); }
    int lift (int u, int k, Path &ans) {
        ans = NIL;
        for (int i = 0; k > 0; i++) {
            if (k & 1) {
                ans += qr[u][i];
                u = up[u][i];
            }
            k >>= 1;
        }
        return u;
    }
    Path path (int u, int v) {
        if (lvl[u] < lvl[v]) swap(u, v);
        Path ans;
        u = lift(u, lvl[u] - lvl[v], ans);
        if (u != v) {
            for (int i = up[u].size() - 1; i >= 0; i--) {
                if (i < up[u].size() && up[u][i] != up[v][i]) {
                    ans += qr[u][i];
                    u = up[u][i];
                    ans += qr[v][i];
                    v = up[v][i];
                }
            }
            ans += qr[u][0] + qr[v][0];
        }
        return ans;
    }
    /* following methods have identical implementations
    as those of "unweighted.cpp":
    int lift (int u, int k);
    int lca (int u, int v);
    int dist (int u, int v); */
};