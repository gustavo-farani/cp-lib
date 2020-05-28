#include "../../../template.cpp"

template<class U, class Q>
struct SegTree {
    vector<U> tree;
    SegTree (int n) : tree(n << 2) {}
    void update (int i, U x, int l, int r, int p = 1) {
        if (i > r || i < l) {
            return;
        } else if (l == r) {
            tree[p] = x;
        } else {
            int m = l + r >> 1;
            int lc = p << 1, rc = (p << 1) + 1;
            update(i, x, l, m, lc);
            update(i, x, m + 1, r, rc);
            // TODO! parent based on children
            tree[p] = tree[lc] + tree[rc];
        }
    }
    Q query (int ql, int qr, int l, int r, int p = 1) {
        if (r < ql || l > qr) {
            // TODO! neutral value
            return 0;
        } else if (ql <= l && r <= qr) {
            // TODO! fully covered sub-range
            return tree[p];
        } else {
            int m = l + r >> 1;
            int lc = p << 1, rc = (p << 1) + 1;
            // TODO! query binary operation
            return query(ql, qr, l, m, lc) + query(ql, qr, m + 1, r, rc);
        }
    }
};