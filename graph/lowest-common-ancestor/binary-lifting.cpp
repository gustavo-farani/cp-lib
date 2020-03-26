#include <vector>
#include "../default/graph.cpp"
#include "../../math/util/floor-lg.cpp"
using namespace std;
    
#define pb push_back
typedef vector<int> vi;
typedef long long ll;

struct Rise {
    int anc;
    ll local;
    Rise (int u = 0) : anc(u), local(0) {}
    Rise operator+ (Rise o) {
        Rise ans;
        ans.anc = o.anc;
        ans.local = max(local, o.local); // !TODO merge paths
        return ans;
    }
    void operator+= (Rise o) { *this = *this + o; }
};

struct BinaryLifting {
    int max_lg;
    vi lvl;
    vector<vector<Rise>> up;
    template<class T> BinaryLifting (const Graph<T>& g, int r) :
       max_lg(floorlg(g.n)), lvl(g.n + 1), up(max_lg + 1, vector<Rise>(g.n + 1))
    {
        function<void(int, int)> dfs = [&] (int u, int par) {
            for (int z : g.adj[u]) {
                int v = u ^ g.edges[z].from ^ g.edges[z].to;
                if (v != par) {
                    lvl[v] = 1 + lvl[u];
                    up[0][v].anc = u;
                    up[0][v].local = g.edges[z].weigth; // !TODO start up with edge from v to u
                    for (int i = 0, a = u; i + 1 <= max_lg; a = up[i++][a].anc) {
                        up[i + 1][v] = up[i][v] + up[i][a];
                    }
                    dfs(v, u);
                }
            }
        };
        dfs(r, r);
    }
    Rise lift (int u, int k) {
        Rise ans(u);
        for (int i = 0; k; i++, k >>= 1) {
            if (k & 1) {
                ans += up[i][u];
                u = ans.anc;
            }
        }
        return ans;
    }
    Rise query (int u, int v) {
        if (lvl[u] < lvl[v]) swap(u, v);
        Rise ans = lift(u, lvl[u] - lvl[v]);
        u = ans.anc;
        if (u != v) {
            for (int i = max_lg; i >= 0; i--) {
                if (up[i][u].anc != up[i][v].anc) {
                    ans += up[i][u];
                    u = ans.anc;
                    ans += up[i][v];
                    v = ans.anc;
                }
            }
            ans += up[0][u] + up[0][v];
        }
        return ans;
    }
    int lca (int u, int v) { return query(u, v).anc; }
    int dist (int u, int v) {
        int w = lca(u, v);
        return lvl[u] + lvl[v] - (lvl[w] << 1);
    }
};