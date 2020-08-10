#include "../../../problem-solving-paradigms/binary-search/coordinate-compression.cpp"

struct DistinctElements {
    struct Node {
        Node *lc, *rc;
        int sum;
        Node (int x) : lc(nullptr), rc(nullptr), sum(x) {}
        Node (Node* lc, Node* rc) : lc(lc), rc(rc), sum(lc->sum + rc->sum) {}
    };
    int n;
    vector<Node*> vs;
    Node* build (int l, int r, vector<bool>& v) {
        if (l == r) {
            return new Node(v[l]);
        } else {
            int m = l + r >> 1;
            return new Node(build(l, m, v), build(m + 1, r, v));
        }
    }
    Node* update (Node* p, int l, int r, int i) {
        if (l == r) {
            return new Node(1);
        } else {
            int m = l + r >> 1;
            if (i <= m) {
                return new Node(update(p->lc, l, m, i), p->rc);
            } else {
                return new Node(p->lc, update(p->rc, m + 1, r, i));
            }
        }
    }
    int query (Node* p, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) {
            return 0;
        } else if (ql <= l && r <= qr) {
            return p->sum;
        } else {
            int m = l + r >> 1;
            return query(p->lc, l, m, ql, qr) + query(p->rc, m + 1, r, ql, qr);
        }
    }
    DistinctElements (vi& a) : n(a.size()) {
        CoordinateCompression<int> cc;
        for (int x : a) cc.push(x);
        vector<list<int>> pos(cc.build());
        vector<bool> v(n);
        for (int i = 0; i < n; i++) {
            int k = cc(a[i]);
            if (pos[k].empty()) v[i] = true;
            pos[k].pb(i);
        }
        vs.pb(build(0, n - 1, v));
        for (int i = 1; i < n; i++) {
            int k = cc(a[i - 1]);
            pos[k].pop_front();
            if (pos[k].empty()) {
                vs.pb(vs.back());
            } else {
                vs.pb(update(vs.back(), 0, n - 1, pos[k].front()));
            }
        }
    }
    // 0-based indexing
    int query (int l, int r) { return query(vs[l], 0, n - 1, l, r); }
};