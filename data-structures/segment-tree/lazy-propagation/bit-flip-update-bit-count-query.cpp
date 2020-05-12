#include "../../../template.cpp"
 
struct BitFlip {
    vi tree;
    vector<bool> lazy;
    BitFlip (int n) :
        tree(n << 2), lazy(n << 2)
    {}
    void refresh (int i, int l, int r) {
        if (lazy[i]) {
            tree[i] = (r - l + 1) - tree[i];
            if (l < r) {
                int lc = (i << 1), rc = (i << 1) + 1;
                lazy[lc] = !lazy[lc];
                lazy[rc] = !lazy[rc];
            }
            lazy[i] = false;
        }
    }
    void update (int i, int l, int r, int ul, int ur) {
        refresh(i, l, r);
        if (r < ul || l > ur) {
            return;
        } else if (ul <= l && r <= ur) {
            lazy[i] = !lazy[i];
            refresh(i, l, r);
        } else {
            int m = l + r >> 1;
            int lc = i << 1, rc = (i << 1) + 1;
            update(lc, l, m, ul, ur);
            update(rc, m + 1, r, ul, ur);
            tree[i] = tree[lc] + tree[rc];
        }
    }
    int query (int i, int l, int r, int ql, int qr) {
        refresh(i, l, r);
        if (r < ql || l > qr) {
            return 0;
        } else if (ql <= l && r <= qr) {
            return tree[i];
        } else {
            int m = l + r >> 1;
            int lc = i << 1, rc = (i << 1) + 1;
            return query(lc, l, m, ql, qr) + query(rc, m + 1, r, ql, qr);
        }
    }
};