#include "../representation/graph.cpp"

struct Edge {
    int from, to;
    int lvl, pos, size;
    Edge* top;
    Edge (int u, int v) : from(u), to(v) {}
};

struct HLD {
    int m;
    vector<Edge*> hang;
    vi l, r;
    // g: tree in edge-list representation
    // vertices in g can either be 0-indexed, or 1-indexed
    // segment tree array will be 1-indexed, with size m
    HLD (Graph& g) : m(0), hang(g.last), l(g.last), r(g.last) {
        function<void(Edge*)> dfs[2];
        dfs[0] = [&] (Edge* f) {
            int& u = f->from;
            f->size = 1;
            for (auto& e : g.adj[u]) {
                if (e != f) {
                    m++;
                    int& v = e->from;
                    if (e->to != u) swap(v, e->to);
                    hang[v] = e;
                    e->lvl = 1 + f->lvl;
                    dfs[0](e);
                    f->size += e->size;
                    auto &h = g.adj[u][0];
                    if (h == f || h->size < e->size) swap(e, h);
                }
            }
        };
        auto s = new Edge(g.first, g.first);
        s->lvl = 0;
        hang[g.first] = s;
        dfs[0](s);
        int t = 0;
        dfs[1] = [&] (Edge* f) {
            int& u = f->from;
            f->pos = t++;
            l[u] = t;
            for (auto e : g.adj[u]) {
                if (e != f) {
                    e->top = e == g.adj[u][0] ? f->top : e;
                    dfs[1](e);
                }
            }
            r[u] = t;
        };
        s->top = s;
        dfs[1](s);
    }
    // returns the position of the edge from u to v on the segment tree array
    int edgePosition (int u, int v) {
        return hang[u]->to == v ? hang[u]->pos : hang[v]->pos;
    }
    // returns the single range of the segment tree array covering
    // all the edges on the subtree rooted on u
    // if u is a leaf, then second < first
    ii subTreeRange (int u) { return {l[u], r[u]}; }
    // returns the ranges of the segment tree array covering
    // the edges along the path from u to v
    // the pair {first, last} represents the range [l, r]
    // (both inclusive) and always first <= last
    // assumes the binary operator for combining ranges of segment tree
    // is commutative (e.g. max/min weight, sum of weights)
    // tested with: https://www.spoj.com/problems/GRASSPLA/
    vector<ii> pathRanges (int u, int v) {
        vector<ii> ans;
        auto e = hang[u], f = hang[v];
        while (e->top != f->top) {
            if (e->top->lvl < f->top->lvl) swap(e, f);
            ans.emplace_back(e->top->pos, e->pos);
            e = hang[e->top->to];
        }
        if (e->lvl > f->lvl) swap(e, f);
        if (e != f) ans.emplace_back(e->pos + 1, f->pos);
        return ans;
    }
    int mirror (int i) { return m - i + 1; }
    // stronger version of method pathRanges
    // vector up contains the ranges of the upward segment tree
    // covering the edges on the path from u to LCA(u, v)
    // vector down contains the ranges of the downward segment tree
    // covering the edges on the path from LCA(u, v) to v
    // TO BE TESTED
    pair<vector<ii>, vector<ii>> orientedPathRanges (int u, int v) {
       vector<ii> up, down;
       auto e = hang[u], f = hang[v];
       while (e->top != f->top) {
           if (e->top->lvl < f->top->lvl) {
               down.emplace_back(f->top->pos, f->pos);
               f = hang[f->top->to];
           } else {
               up.emplace_back(mirror(e->pos), mirror(e->top->pos));
               e = hang[e->top->to];
           }
       }
       if (e->lvl > f->lvl) {
           up.emplace_back(mirror(e->pos), mirror(f->pos + 1));
       } else if (e->lvl < f->lvl) {
           down.emplace_back(e->pos + 1, f->pos);
       }
       reverse(down.begin(), down.end());
       return {up, down};
    }
};