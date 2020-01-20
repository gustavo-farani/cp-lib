#include <vector>
using namespace std;

#define pb push_back
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

struct LCA {  // binary lifting for path length query
    vector< vector<ii> > adj;  // weighted tree
    int cnt;
    vi pre, post;    // pre-visit and post-visit dfs timer
    vector<vi> up;   // ancestors matrix (dynamically allocated)
    vector< vector<ll> > d;
    LCA (int n) :  // 1-based
        adj(n + 1), cnt(0), pre(n + 1),
        post(n + 1), up(n + 1), d(n + 1)
    {}
    void addEdge (int u, int v, int w) {
        adj[u].pb({w, v});
        adj[v].pb({w, u});
    }
    void dfs (int u, int par) {
        pre[u] = cnt++;
        for (ii &e : adj[u]) {
            int v = e.second, l = e.first;
            if (v != par) {
                up[v].pb(u);
                d[v].pb(l);
                for (int i = 0, w = u; i < up[w].size(); i++) {
                    up[v].pb(up[w][i]);
                    d[v].pb(d[v].back() + d[w][i]);
                    w = up[v].back();
                }
                dfs(v, u);
            }
        }
        post[u] = cnt++;
    }
    void build (int r) { dfs(r, r); }
    bool ancestor (int u, int v) {
        return (pre[u] <= pre[v] && post[u] >= post[v]);
    }
    ll lift (int u, int v) {
        ll sum = 0;
        for (int i = up[u].size() - 1; i >= 0; i--) {
            if (i < up[u].size() && !ancestor(up[u][i], v)) {
                sum += d[u][i];
                u = up[u][i];
            }
        }
        return sum + d[u][0];
    }
    ll dist (int u, int v) {
        if (ancestor(u, v)) {
            return lift(v, u);
        } else if (ancestor(v, u)) {
            return lift(u, v);
        } else {
            return lift(u, v) + lift(v, u);
        }
    }
};