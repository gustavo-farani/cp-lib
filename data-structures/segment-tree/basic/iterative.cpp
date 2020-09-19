#include "../../../boilerplate.cpp"
#include "../../../math/bitmasks/lg.cpp"

template<bool B, class T>
struct SegmentTree {
    struct Node {
        // binary operation for getting the parent node
        // by merging its left and right children
        // operation must be associative and run in constant time
        Node (const Node& l, const Node& r) {}
        // the default initialization should correspond
        // to the neutral operand in the binary operation
        Node () {}
        // for updating a leaf node
        Node (const T& x) {}
    };
    int n;
    vector<Node> tree;
    SegmentTree (int n) : n(1 << ceilLg(n)), tree(this->n << 1) {}
    // updates a leaf
    void at (int i, const T& x) { tree[i - B + n] = x; }
    // initialization of the whole tree
    void build () {
        for (int p = n; p--;) tree[p] = {tree[p << 1], tree[p << 1 | 1]};
    }
    // updates a leaf and every ancestor of it
    void update (int i, const T& x) {
        at(i, x);
        i -= B;
        for (int p = i + n >> 1; p > 0; p >>= 1) {
            tree[p] = {tree[p << 1], tree[p << 1 | 1]};
        }
    }
    // [l, r]: closed interval
    Node query (int l, int r) {
        l -= B, r -= B;
        Node lh, rh;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) lh = {lh, tree[l++]};
            if (r & 1) rh = {tree[--r], rh};
        }
        return {lh, rh};
    }
};