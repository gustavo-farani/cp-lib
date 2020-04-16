#include <vector>
using namespace std;

struct Node {
    Node operator+ (Node o);
    void leaf (int x);
} NIL;

template<class T>
struct SegmentTree {
    vector<Node> tree;
    SegmentTree (int n) :
        tree(n << 2, NIL)
    {}
    void update (int i, int l, int r, int p, T x) {
        if (p > r || p < l) {
            return;
        } else if (l == r) {
            tree[i].leaf(x);
        } else {
            int m = l + r >> 1;
            int lc = i << 1, rc = (i << 1) + 1;
            update(lc, l, m, p, x);
            update(rc, m + 1, r, p, x);
            tree[i] = tree[lc] + tree[rc];
        }
    }
    Node query (int i, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) {
            return NIL;
        } else if (ql <= l && r <= qr) {
            return tree[i];
        } else {
            int m = l + r >> 1;
            int lc = i << 1, rc = (i << 1) + 1;
            return query(lc, l, m, ql, qr) + query(rc, m + 1, r, ql, qr);
        }
    }
};