#include "../../../template.cpp"

template<class T>
struct RangeMaximumSum {
    struct Node {
        T ans, sum, pref, suf;
        void leaf (T x) {
            ans = sum = pref = suf = x;
        }
        void merge (const Node& left, const Node& right) {
            ans = max({left.ans, right.ans, left.suf + right.pref});
            sum = left.sum + right.sum;
            pref = max(left.pref, left.sum + right.pref);
            suf = max(right.suf, right.sum + left.suf);
        }
    };
    vector<Node> tree;
    RangeMaximumSum (int n, const vector<T>& v) : tree(n << 2) {
        build(1, 0, n - 1, v);  // 0-based
    }
    void build (int p, int l, int r, const vector<T>& v) {
        if (l == r) {
            tree[p].leaf(v[l]);
        } else {
            int m = l + r >> 1;
            int lc = p << 1, rc = (p << 1) + 1;
            build(lc, l, m, v);
            build(rc, m + 1, r, v);
            tree[p].merge(tree[lc], tree[rc]);
        }
    }
    void update (int p, int l, int r, int i, T x) {
        if (i < l || i > r) {
            return;
        } else if (l == r) {
            tree[p].leaf(x);
        } else {
            int m = l + r >> 1;
            int lc = p << 1, rc = (p << 1) + 1;
            update(lc, l, m, i, x);
            update(rc, m + 1, r, i, x);
            tree[p].merge(tree[lc], tree[rc]);
        }
    }
    Node query (int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[p];
        } else {
            int m = l + r >> 1;
            int lc = p << 1, rc = (p << 1) + 1;
            Node par;
            if (qr <= m) {
                par = query(lc, l, m, ql, qr);
            } else if (ql > m) {
                par = query(rc, m + 1, r, ql, qr);
            } else {
                par.merge(query(lc, l, m, ql, qr),
                query(rc, m + 1, r, ql, qr));
            }
            return par;
        }
    }
};