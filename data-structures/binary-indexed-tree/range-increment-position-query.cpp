#include "binary-indexed-tree.cpp"

// B: base indexation for array indices
template<class T, bool B>
struct RangeIncrement {
    BIT<T> v;
    RangeIncrement (int n) : v(n + 1) {}
    // range increment
    void add (int l, int r, T x) {
        v.update(l + !B, x);
        v.update(r + !B + 1, -x);
    }
    // position query
    T at (int i) { return v.prefix(i + !B); }
};