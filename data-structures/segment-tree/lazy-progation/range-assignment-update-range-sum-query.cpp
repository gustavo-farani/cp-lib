#include <vector>
#include <tuple>
using namespace std;

typedef long long ll;

struct RangeAssign {
    vector<ll> tree;
    vector<pair<bool, int>> lazy;
    RangeAssign (int n) :
        tree(n << 2), lazy(n << 2)
    {}
    void refresh (int i, int l, int r) {
        if (lazy[i].first) {
            tree[i] = (ll) (r - l + 1) * lazy[i].second;
            if (l < r) {
                int lc = i << 1, rc = (i << 1) + 1;
                lazy[lc] = lazy[rc] = lazy[i];
            }
            lazy[i].first = false;
        }
    }
    void update (int i, int l, int r, int ul, int ur, int x) {
        refresh(i, l, r);
        if (r < ul || l > ur) {
            return;
        } else if (ul <= l && r <= ur) {
            lazy[i] = {true, x};
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