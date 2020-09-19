#include "../../../boilerplate.cpp"

const double EPS = 1e-9;
 
// cross product in floating point only because of overflow reasons
bool cw (double ux, double uy, double vx, double vy) {
    return ux*vy - uy*vx < EPS;
}
 
struct Line {
    ll m, b, x, k;
    bool q;
    Line (bool q, ll v, ll w = 1) : q(q) {
        if (q) {
            x = v;
            k = w;
        } else {
            m = v;
            b = w;
        }
    }
    bool operator< (const Line& o) const {
        if (q) {
            return !cw(x, k, o.x, o.k);
        } else if (m == o.m) {
            return b < o.b;
        } else {
            return m < o.m;
        }
    }
    void set (Line p) {
        x = p.b - b;
        k = m - p.m;
    }
    bool concave (Line l, Line r) const {
        return cw(m - l.m, b - l.b, r.m - m, r.b - b);
    }
    ll eval (ll x) const { return m*x + b; }
};
 
// CHT: Convex Hull Trick
// insertions are handled online, and may be interchanged with queries
struct CHT {
    set<Line> h;
    // inserts the linear function f(x) = mx + b
    // m, b can be either positive or negative
    // time complexity: amortizedly O(N lg N), for N insertions
    void insert (ll m, ll b) {
        Line l(false, m, b);
        auto s = h.lower_bound(l);
        if (!h.empty()) {
            bool hs = s != h.end(), hp = s != h.begin();
            if (!hs && prev(s)->m == l.m || hs &&
            (l.m == s->m && l.b == s->b || hp && l.concave(*prev(s), *s))) {
                return;
            }
            if (hp) {
                auto p = prev(s);
                while (p != h.begin() && p->concave(*prev(p), l)) {
                    p = prev(h.erase(p));
                }
            }
            if (hs) {
                auto t = next(s);
                while (t != h.end() && s->concave(l, *t)) {
                    s = h.erase(s);
                    t = next(s);
                }
            }
            if (s != h.end() && s->m == l.m) {
                s = h.erase(s);
            }
        }
        if (s == h.begin()) {
            l.x = 1;
            l.k = 0;
        } else {
            l.set(*prev(s));
        }
        if (s != h.end()) {
            Line r = *s;
            r.set(l);
            s = h.erase(s);
            h.insert(s, r);
        }
        h.insert(s, l);
    }
    // returns the minimum possible f(x) for any function f inserted
    // x can either be positive or negative
    // time complexity: O(lg N), for each query
    ll minimum (ll x) {
        Line q(true, x);
        auto s = h.upper_bound(q);
        return prev(s)->eval(x);
    }
};

// tested successfully with problem:
// https://codeforces.com/problemset/problem/932/F