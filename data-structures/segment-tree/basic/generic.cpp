#include <vector>
using namespace std;

struct Node {
    Node operator+ (Node o);
    void leaf (int x);
} NIL;

template<class T>
struct SegTree {
    vector<Node> tree;
    SegTree (int n) :   // 0-based
        tree(n << 2, NIL)
    {}
    void update (int i, int l, int r, int p, T x) {
        if (p > r || p < l) {
            return;
        } else if (l == r) {
            tree[i].leaf(x);
        } else {
            int m = (l + r) >> 1;
            int fe = i << 1, fd = (i << 1) + 1;
            update(fe, l, m, p, x);
            update(fd, m + 1, r, p, x);
            tree[i] = tree[fe] + tree[fd];
        }
    }
    Node query (int i, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) {
            return NIL;
        } else if (ql <= l && r <= qr) {
            return tree[i];
        } else {
            int m = (l + r) >> 1;
            int fe = i << 1, fd = (i << 1) + 1;
            return query(fe, l, m, ql, qr) + query(fd, m + 1, r, ql, qr);
        }
    }
};