#include "../../representation/weighted-graph.cpp"

struct HLD {
    vi lvl, par, pre, post, top;
    vector<ll> dist;
    // g: tree in weighted-graph representation
    // vertices in g can either be 0-indexed, or 1-indexed
    // ith vertice in g will be mapped to position pre[i]
    // of segment tree array
    // segment tree array will be 1-based, with size g.n
    HLD (WeightedGraph& g) :
        lvl(g.last), par(g.last), pre(g.last),
        post(g.last), top(g.last), dist(g.last)
    {
        vi sz(g.last);
        function<void(int)> dfs[2];
        dfs[0] = [&] (int u) {
            sz[u] = 1;
            for (auto it = g.adj[u].begin(); it != g.adj[u].end(); it++) {
                auto [w, v] = *it;    // C++ 17 only
                if (v != par[u]) {
                    lvl[v] = 1 + lvl[u];
                    par[v] = u;
                    dist[v] = w + dist[u];
                    dfs[0](v);
                    sz[u] += sz[v];
                    auto jt = g.adj[u].begin();
                    if (jt->second == par[u] || sz[v] > sz[jt->second]) {
                        iter_swap(it, jt);
                    }
                }
            }
        };
        dfs[0](par[g.first] = g.first);
        int t = 0;
        dfs[1] = [&] (int u) {
            pre[u] = ++t;
            for (auto it = g.adj[u].begin(); it != g.adj[u].end(); it++) {
                int v = it->second;
                if (v != par[u]) {
                    top[v] = it == g.adj[u].begin() ? top[u] : v;
                    dfs[1](v);
                }
            }
            post[u] = t;
        };
        dfs[1](top[g.first] = g.first);
    }
    // the range of the segment tree including all the nodes
    // in the subtree rooted at u
    ii subtree (int u) {
        return {pre[u], post[u]};
    }
    // sum of the weights of the edges along the path from u to v
    // assumes edge weights are constant
    ll distance (int u, int v) {
        ll sum = 0;
        while (top[u] != top[v]) {
            if (lvl[top[u]] < lvl[top[v]]) swap(u, v);
            sum += dist[u] - dist[par[top[u]]];
            u = par[top[u]];
        }
        if (lvl[u] < lvl[v]) swap(u, v);
        sum += dist[u] - dist[v];
        return sum;
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
    vector<ii> unorderedPath (int u, int v) {
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
    // stronger version of method unorderedPath
    // vector up contains the ranges going updwards from u to LCA(u, v)
    // vector down contains the ranges going downwards from LCA(u, v) to v
    // both up and down contains pairs {first, last} == [l, r], representing
    // range [l, r] (both inclusive)
    // always first <= last, so the ranges start from the upper vertex and
    // end at the lower vertex
    // so if the path from u to v must be scanned sequentially,
    // ranges [l, r] in vector up must be processed in reverse order,
    // because as u ascends to LCA(u, v), it first passes through the lower
    // vertices, and then reach the upper ones (while the ranges [l,r] in
    // vector up suggest the opposite)
    pair<vector<ii>, vector<ii>> orderedPath (int u, int v) {
        vector<ii> up, down;
        while (top[u] != top[v]) {
            if (lvl[top[u]] < lvl[top[v]]) {
                down.emplace_back(pre[top[v]], pre[v]);
                v = par[top[v]];
            } else {
                up.emplace_back(pre[top[u]], pre[u]);
                u = par[top[u]];
            }
        }
        if (lvl[u] < lvl[v]) down.emplace_back(pre[u], pre[v]);
        else up.emplace_back(pre[v], pre[u]);
        reverse(down.begin(), down.end());
        return {up, down};
    }
};