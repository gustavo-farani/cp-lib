#include <vector>
using namespace std;

typedef long long ll;

struct Node {
    Node operator+ (const Node &o);
    void assign (ll x, int l, int r) {}
} NIL;

struct Todo {
    bool empty () {}
    void pop () {}
    void push (ll x) {}
    ll top () {}
};

template<class T>
struct LazyPropagation {
    vector<Node> tree;
    vector<Todo> lazy;
    LazyPropagation (int n) :
        tree(n << 2, NIL), lazy(n << 2)
    {}
    void refresh (int i, int l, int r) {
        while (!lazy[i].empty()) {
            tree[i].assign(lazy[i].top(), l, r);
            if (l < r) {
                int lc = i << 1, rc = (i << 1) + 1;
                lazy[lc].push(lazy[i].top());
                lazy[rc].push(lazy[i].top());
            }
            lazy[i].pop();
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