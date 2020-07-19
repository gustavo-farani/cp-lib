#include "../../representation/weighted-graph.cpp"

const int MAX_LG = 20;  // TODO adjust maximum lg(|V|) according to input size

struct BinaryLifting {  // offline tree path query
    struct TreePath {
        int anc;
        ll best;
        TreePath (int u = 0) : anc(u), best(0) {}
        TreePath operator+ (TreePath o) {
            TreePath ans;
            ans.anc = o.anc;
            ans.best = max(best, o.best); // !TODO merge paths
            return ans;
        }
        void operator+= (TreePath o) { *this = *this + o; }
    };
    vi lvl;
    vector<vector<TreePath>> up;
    BinaryLifting (const Graph& g) :
       lvl(g.last), up(MAX_LG + 1, vector<TreePath>(g.last))
    {  // g: weighted tree in neighbour list representation
        function<void(int, int)> dfs = [&] (int u, int par) {
            for (auto [w, v] : g.adj[u]) {  // C++ 17
                if (v != par) {
                    lvl[v] = 1 + lvl[u];
                    up[0][v].anc = u;
                    up[0][v].best = w; // !TODO start up with edge from v to u
                    for (int i = 0, a = u; i + 1 <= MAX_LG; a = up[i++][a].anc) {
                        up[i + 1][v] = up[i][v] + up[i][a];
                    }
                    dfs(v, u);
                }
            }
        };
        dfs(g.first, g.first);
    }
    TreePath lift (int u, int k) {
        TreePath ans(u);
        for (int i = 0; k; i++, k >>= 1) {
            if (k & 1) {
                ans += up[i][u];
                u = ans.anc;
            }
        }
        return ans;
    }
    TreePath query (int u, int v) {
        if (lvl[u] < lvl[v]) swap(u, v);
        TreePath ans = lift(u, lvl[u] - lvl[v]);
        u = ans.anc;
        if (u != v) {
            for (int i = MAX_LG; i >= 0; i--) {
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