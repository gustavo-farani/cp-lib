#include "binary-indexed-tree.cpp"

// B: base indexation for array indices
template<class T, bool B>
struct RangeSum {
    BIT<T> v;
    RangeIncrement (int n) : v(n) {}
    // position increment
    void add (int i, T x) { v.update(i + !B, x); }
    // range sum
    T sum (int l, int r) { return v.prefix(r + !B) - v.prefix(l - B); }
};