#include <vector>
using namespace std;

typedef long long ll;

struct RangeIncrement {
    vector<ll> tree, lazy;
    RangeIncrement (int n) :
        tree(n << 2), lazy(n << 2)
    {}
    void refresh (int i, int l, int r) {
        if (lazy[i] != 0) {
            tree[i] += lazy[i] * (r - l + 1);
            if (l < r) {
                int lc = i << 1, rc = (i << 1) + 1;
                lazy[lc] += lazy[i];
                lazy[rc] += lazy[i];
            }
            lazy[i] = 0;
        }
    }
    void update (int i, int l, int r, int ul, int ur, ll x) {
        refresh(i, l, r);
        if (r < ul || l > ur) {
            return;
        } else if (ul <= l && r <= ur) {
            lazy[i] += x;
            refresh(i, l, r);
        } else {
            int m = l + r >> 1;
            int lc = i << 1, rc = (i << 1) + 1;
            update(lc, l, m, ul, ur, x);
            update(rc, m + 1, r, ul, ur, x);
            tree[i] = tree[lc] + tree[rc];
        }
    }
    ll query (int i, int l, int r, int ql, int qr) {
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