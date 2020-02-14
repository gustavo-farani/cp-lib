#include <vector>
using namespace std;

struct Todo {
    bool empty () {}
    void clear () {}
    void operator>> (const Todo& o) {}
    void operator<< (const Todo& o) {}
};

struct Node {
    Node operator+ (const Node &o) {}
    void assign (const Todo &t, int l, int r) {}
} NIL;

template<class T>
struct LazyPropagation {
    vector<Node> tree;
    vector<Todo> lazy;
    LazyPropagation (int n) :
        tree(n << 2, NIL), lazy(n << 2)
    {}
    void refresh (int i, int l, int r) {
        if (!lazy[i].empty()) {
            tree[i].assign(lazy[i], l, r);
            if (l < r) {
                int lc = i << 1, rc = (i << 1) + 1;
                lazy[i] << lazy[lc];
                lazy[i] >> lazy[rc];
            }
            lazy[i].clear();
        }
    }
    void update (int i, int l, int r, int ul, int ur, T x) {
        refresh(i, l, r);
        if (r < ul || l > ur) {
            return;
        } else if (ul <= l && r <= ur) {
            lazy[i].push(x);
            refresh(i, l, r);
        } else {
            int m = (l + r) >> 1;
            int lc = i << 1, rc = (i << 1) + 1;
            update(lc, l, m, ul, ur, x);
            update(rc, m + 1, r, ul, ur, x);
            tree[i] = tree[lc] + tree[rc];
        }
    }
    Node query (int i, int l, int r, int ql, int qr) {
        refresh(i, l, r);
        if (r < ql || l > qr) {
            return NIL;
        } else if (ql <= l && r <= qr) {
            return tree[i];
        } else {
            int m = (l + r) >> 1;
            int lc = i << 1, rc = (i << 1) + 1;
            return query(lc, l, m, ql, qr) + query(rc, m + 1, r, ql, qr);
        }
    }
};