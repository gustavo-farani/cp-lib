#include "../../../template.cpp"

template<class T>
struct SegmentTree {
    vector<T> tree;
    function<void(T&, int)> leaf;
    function<void(T&, T&, T&)> merge;
    SegmentTree (int n, decltype(leaf) leaf, decltype(merge) merge) :
        tree(n << 2), leaf(leaf), merge(merge) 
    {}
    void build (int p, int l, int r, const vi& a) {
        if (l == r) {
            leaf(tree[p], a[l]);
        } else {
            int m = l + r >> 1, lc = p << 1, rc = lc + 1;
            build(lc, l, m, a);
            build(rc, m + 1, r, a);
            merge(tree[p], tree[lc], tree[rc]);
        }
    }
    void update (int p, int l, int r, int i, int x) {
        if (l == r) {
            leaf(tree[p], x);
        } else {
            int m = l + r >> 1, lc = p << 1, rc = lc + 1;
            if (i <= m) update(lc, l, m, i, x);
            else update(rc, m + 1, r, i, x);
            merge(tree[p], tree[lc], tree[rc]);
        }
    }
    T query (int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[p];
        } else {
            int m = l + r >> 1, lc = p << 1, rc = lc + 1;
            if (qr <= m) {
                return query(lc, l, m, ql, qr);
            } else if (ql > m) {
                return query(rc, m + 1, r, ql, qr);
            } else {
                T par;
                merge(par, query(lc, l, m, ql, qr),
                query(rc, m + 1, r, ql, qr));
                return par;
            }
        }
    }
};