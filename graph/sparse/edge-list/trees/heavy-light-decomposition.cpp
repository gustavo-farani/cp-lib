#include "../representation/graph.cpp"

struct HLD {
    vi hang, lvl, par, pre, top;
    // g: tree in edge-list representation
    // vertices in g can either be 0-indexed, or 1-indexed
    // edges in g must be 0-indexed
    // ith edge in g will be mapped to position pre[i]
    // of segment tree array
    // segment tree array will be 1-indexed,
    // with size g.n - 1 (g is tree)
    template<class T> HLD (Graph<T>& g) :
        hang(g.last), lvl(g.n), par(g.n), pre(g.n), top(g.n)
    {
        vi sz(g.n);
        function<void(int)> dfs[2];
        dfs[0] = [&] (int u) {
            int i = hang[u];
            sz[i] = 1;
            for (int &j : g.adj[u]) {
                if (j != i) {
                    int v = u ^ g.e[j].from ^ g.e[j].to;
                    hang[v] = j;
                    lvl[j] = 1 + lvl[i];
                    par[j] = i;
                    dfs[0](v);
                    sz[i] += sz[j];
                    int &k = g.adj[u].front();
                    if (k == i || sz[k] < sz[j]) swap(j, k);
                }
            }
        };
        hang[g.first] = g.n - 1;
        lvl[g.n - 1] = 0;
        dfs[0](g.first);
        int t = 0;
        dfs[1] = [&] (int u) {
            int i = hang[u];
            for (int j : g.adj[u]) {
                if (j != i) {
                    int v = u ^ g.e[j].from ^ g.e[j].to;
                    pre[j] = ++t;
                    top[j] = j == g.adj[u].front() ? top[i] : j;
                    dfs[1](v);
                }
            }
        };
        top[g.n - 1] = g.n - 1;
        dfs[1](g.first);
    }
    // returns the ranges of the segment tree array covering
    // the edges along the path from u to v
    // the pair {first, last} represents the range [l, r]
    // (both inclusive) and always first <= last
    // assumes the binary operator for combining ranges of segment tree
    // is commutative (e.g. max/min weight, sum of weights)
    vector<ii> unorderedPath (int u, int v) {
        vector<ii> ans;
        int i = hang[u], j = hang[v];
        while (top[i] != top[j]) {
            if (lvl[top[i]] < lvl[top[j]]) swap(i, j);
            ans.emplace_back(pre[top[i]], pre[i]);
            i = par[top[i]];
        }
        if (lvl[i] > lvl[j]) swap(i, j);
        if (i != j) ans.emplace_back(pre[i] + 1, pre[j]);
        return ans;
    }
    pair<vector<ii>, vector<ii>> orderedPath (int u, int v) {
       vector<ii> up, down;
       int i = hang[u], j = hang[v];
       while (top[i] != top[j]) {
           if (lvl[top[i]] < lvl[top[j]]) {
               down.emplace_back(pre[top[j]], pre[j]);
               j = par[top[j]];
           } else {
               up.emplace_back(pre[i], pre[top[i]]);
               i = par[top[i]];
           }
       }
       if (lvl[i] > lvl[j]) up.emplace_back(pre[i], pre[j] + 1);
       else down.emplace_back(pre[i] + 1, pre[j]);
       reverse(down.begin(), down.end());
       return {up, down};
    }
};