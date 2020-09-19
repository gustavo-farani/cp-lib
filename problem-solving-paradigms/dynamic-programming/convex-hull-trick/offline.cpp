#include "../../../problem-solving-paradigms/binary-search/monotonically-increasing.cpp"
#include "../../../computational-geometry/2D/integer/point.cpp"

// CHT: Convex Hull Trick
// has support for both maximum and minimum dot product queries
// all insertions must be passed offline to the constructor, before any query
struct CHT {
    vector<PT> h[2];
    const int sgn[2] = {1, -1};
    CHT (vector<PT>& in) {
        sort(in.begin(), in.end());
        in.erase(unique(in.begin(), in.end()), in.end());
        build(0, in);  // upper hull
        build(1, in);  // lower hull
    }
    void build (bool b, vector<PT>& in) {
        int n = 0;
        for (PT& p : in) {
            while (n > 1 && sgn[b]*orient(h[b][n - 2], h[b][n - 1], p) >= 0) {
                h[b].resize(--n);
            }
            h[b].resize(++n, p);
        }
    }
    bool half (PT q) { return q.y < 0 || q.y == 0 && q.x < 0; }
    PT find (PT q, bool b) {
        if (half(q)) {
            return find(q*-1, !b);
        } else if (h[b].size() == 1) {
            return h[b][0];
        } else {
            int i = search(0, h[b].size() - 2, [&] (int i) {
                return q*sgn[b]*(h[b][i] - h[b][i + 1]) >= 0;
            });
            return h[b][i];
        }
    }
    // returns the point in the input set
    // yielding the maximum dot product with q
    PT argmax (PT q) { return find(q, 0); }
    // returns the point in the input set
    // yielding the minimum dot product with q
    PT argmin (PT q) { return find(q, 1); }
    // returns the maximum possible dot product between q
    // and any point in the input set
    ll max (PT q) { return argmax(q)*q; }
    // returns the minimum possible dot product between q
    // and any point in the input set
    ll min (PT q) { return argmin(q)*q; }
};