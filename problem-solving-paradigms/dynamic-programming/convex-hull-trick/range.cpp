#include "../../../computational-geometry/2D/integer/point.cpp"
#include "../../binary-search/monotonically-increasing.cpp"

struct Node {
    vector<pair<PT, int>> h;
    Node () {}
    Node (int i, ll m, ll b) : h({{PT(m, b), i}}) {}
    Node (const Node& l, const Node& r) {
        vector<pair<PT, int>> in(l.h.size() + r.h.size());
        merge(l.h.begin(), l.h.end(), r.h.begin(), r.h.end(), in.begin());
        int n = 0;
        for (auto& it : in) {
            while (n > 1 && orient(h[n - 2].fi,
            h[n - 1].fi, it.fi) >= 0) {
                h.resize(--n);
            }
            h.resize(++n, it);
        }
    }
    pair<ll, int> max (ll x) {
        PT q(x, 1);
        int i;
        if (h.size() == 1) {
            i = 0;
        } else {
            i = search(0, h.size() - 2, [&] (int i) {
                return q*(h[i].fi - h[i + 1].fi) >= 0;
            });
        }
        return {h[i].fi*q, h[i].se};
    }
};

// Segment tree for convex hull trick queries on ranges
// Finds not only the maximum y value for a given x, but also the position
// in the array of the linear function responsible for it
// Works offline; has no support for updates
struct CHT {
    vector<Node> tree;
    CHT (int n) : tree(n << 2) {}
    // a: slope of each line
    // b: intercept with y axis of each line
    void build (int p, int l, int r, vector<ll>& a, vector<ll>& b) {
        if (l == r) {
            tree[p] = {l, a[l], b[l]};
        } else {
            int m = l + r >> 1, lc = p << 1, rc = lc + 1;
            build(lc, l, m, a, b);
            build(rc, m + 1, r, a, b);
            tree[p] = {tree[lc], tree[rc]};
        }
    }
    // first: max a[i]*x + b[i], for l <= i <= r
    // second: argmax a[i]*x + b[i], for l <= i <= r
    pair<ll, int> query (int p, int l, int r, int ql, int qr, ll x) {
        if (ql <= l && r <= qr) {
            return tree[p].max(x);
        } else {
            int m = l + r >> 1, lc = p << 1, rc = lc + 1;
            if (qr <= m) {
                return query(lc, l, m, ql, qr, x);
            } else if (ql > m) {
                return query(rc, m + 1, r, ql, qr, x);
            } else {
                return max(query(lc, l, m, ql, qr, x),
                query(rc, m + 1, r, ql, qr, x));
            }
        }
    }
};

// tested successfully with problem:
// https://codeforces.com/problemset/problem/91/E