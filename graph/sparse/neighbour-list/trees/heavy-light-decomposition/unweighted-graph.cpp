#include "../../representation/unweighted-graph.cpp"

struct HLD {
    int n;
    vi lvl, par, pre, post, top;
    // g: tree in unweighted-graph representation
    // vertices in g can either be 0-indexed, or 1-indexed
    // ith vertice in g will be mapped to position pre[i] of segment tree array
    // segment tree array will be 1-based, with size n
    HLD (Graph& g) :
        n(0), lvl(g.last), par(g.last), pre(g.last), post(g.last), top(g.last)
    {
        vi sz(g.last);
        function<void(int)> dfs[2];
        dfs[0] = [&] (int u) {
            n++;
            sz[u] = 1;
            for (int &v : g.adj[u]) {
                if (v != par[u]) {
                    lvl[v] = 1 + lvl[u];
                    par[v] = u;
                    dfs[0](v);
                    sz[u] += sz[v];
                    int& w = g.adj[u].front();
                    if (w == par[u] || sz[v] > sz[w]) swap(v, w);
                }
            }
        };
        dfs[0](par[g.first] = g.first);
        int t = 0;
        dfs[1] = [&] (int u) {
            pre[u] = ++t;
            for (int v : g.adj[u]) {
                if (v != par[u]) {
                    top[v] = v == g.adj[u].front() ? top[u] : v;
                    dfs[1](v);
                }
            }
            post[u] = t;
        };
        dfs[1](top[g.first] = g.first);
    }
    int mirror (int i) { return n - i + 1; }
    // lowest common ancestor of u and v
    int lca (int u, int v) {
        while (top[u] != top[v]) {
            if (lvl[top[u]] < lvl[top[v]]) swap(u, v);
            u = par[top[u]];
        }
        if (lvl[u] > lvl[v]) swap(u, v);
        return u;
    }
    // number of edges in the path from u to v
    int dist (int u, int v) {
        return lvl[u] + lvl[v] - (lvl[lca(u, v)] << 1);
    }
    // the range of the segment tree including all the nodes
    // in the subtree rooted at u
    ii subTreeRange (int u) {
        return {pre[u], post[u]};
    }
    // returns the ranges of the segment tree array covering
    // the vertices along the path from u to v
    // the pair {first, last} represents the range [l, r] (both inclusive)
    // always first <= last, so the ranges start from the upper vertex and
    // end at the lower vertex
    // assumes the binary operator for combining ranges of segment tree
    // is commutative (e.g. max/min weight, sum of weights), so the order
    // in which the information on ranges are combined won't respect
    // the actual sequence of vertices from u to v
    vector<ii> pathRanges (int u, int v) {
        vector<ii> ans;
        while (top[u] != top[v]) {
            if (lvl[top[u]] < lvl[top[v]]) swap(u, v);
            ans.emplace_back(pre[top[u]], pre[u]);
            u = par[top[u]];
        }
        if (lvl[u] > lvl[v]) swap(u, v);
        ans.emplace_back(pre[u], pre[v]);
        return ans;
    }
    // stronger version of method pathRanges
    // vector up contains the ranges of the upward segment tree
    // covering the edges on the path from u to LCA(u, v)
    // vector down contains the ranges of the downward segment tree
    // covering the edges on the path from LCA(u, v) to v
    // tested with: https://codeforces.com/gym/101908/problem/H
    pair<vector<ii>, vector<ii>> orientedPathRanges (int u, int v) {
        vector<ii> up, down;
        while (top[u] != top[v]) {
            if (lvl[top[u]] < lvl[top[v]]) {
                down.emplace_back(pre[top[v]], pre[v]);
                v = par[top[v]];
            } else {
                up.emplace_back(mirror(pre[u]), mirror(pre[top[u]]));
                u = par[top[u]];
            }
        }
        if (lvl[u] < lvl[v]) {
            down.emplace_back(pre[u], pre[v]);
        } else {
            up.emplace_back(mirror(pre[u]), mirror(pre[v]));
        }
        reverse(down.begin(), down.end());
        return {up, down};
    }
};