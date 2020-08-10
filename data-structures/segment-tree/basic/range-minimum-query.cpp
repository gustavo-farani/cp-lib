#include "../../../boilerplate.cpp"

template<class T>
struct RangeMin {
    vector<T> tree;
    RangeMin (int n, T x = numeric_limits<T>::max()) : tree(n << 2, x) {}
    void update (int p, int l, int r, int i, T x) {
        if (l == r) {
            tree[p] = x;
        } else {
            int m = l + r >> 1, lc = p << 1, rc = (p << 1) + 1;
            if (i <= m) update(lc, l, m, i, x);
            else update(rc, m + 1, r, i, x);
            tree[p] = min(tree[lc], tree[rc]);
        }
    }
    T query (int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[p];
        } else {
            int m = l + r >> 1, lc = p << 1, rc = (p << 1) + 1;
            if (qr <= m) {
                return query(lc, l, m, ql, qr);
            } else if (ql > m) {
                return query(rc, m + 1, r, ql, qr);
            } else {
                return min(query(lc, l, m, ql, qr),
                           query(rc, m + 1, r, ql, qr));
            }
        }
    }
};