#include "../../../template.cpp"

template<class T>
struct RangeMax {
    vector<T> tree;
    RangeMax (int n) : tree(n << 2, numeric_limits<T>::min()) {}
    void update (int i, int l, int r, int p, T x) {
        if (p > r || p < l) {
            return;
        } else if (l == r) {
            tree[i] = x;
        } else {
            int m = l + r >> 1;
            int lc = i << 1, rc = (i << 1) + 1;
            update(lc, l, m, p, x);
            update(rc, m + 1, r, p, x);
            tree[i] = max(tree[lc], tree[rc]);
        }
    }
    T query (int i, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) {
            return numeric_limits<T>::min();
        } else if (ql <= l && r <= qr) {
            return tree[i];
        } else {
            int m = l + r >> 1;
            int lc = i << 1, rc = (i << 1) + 1;
            return max(query(lc, l, m, ql, qr), query(rc, m + 1, r, ql, qr));
        }
    }
};