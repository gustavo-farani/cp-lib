namespace SegmentTree {
    // smallest power of 2 greater than maximum array size
    const int N = 131072;
    // base-indexation for the indices (either 0 or 1)
    const bool B = 0;
    struct Node {
        // binary operation for getting the parent node
        // by merging its left and right children
        // operation must be associative and run in constant time
        Node(const Node& l, const Node& r);
        // the default initialization should correspond
        // to the neutral operand in the binary operation
        Node();
        // for updating a leaf node
        Node(int x);
    } tree[N << 1];
    // updates a leaf
    void at (int i, int x) { tree[i - B + N] = x; }
    // initialization of the whole tree
    void build () {
        for (int p = N; p--;) tree[p] = {tree[p << 1], tree[p << 1 | 1]};
    }
    // updates a leaf and every ancestor of it
    void update (int i, int x) {
        at(i, x);
        i -= B;
        for (int p = i + N >> 1; p > 0; p >>= 1) {
            tree[p] = {tree[p << 1], tree[p << 1 | 1]};
        }
    }
    // [ql, qr]: closed interval
    Node query (int l, int r) {
        l -= B, r -= B;
        Node lh, rh;
        for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) lh = {lh, tree[l++]};
            if (r & 1) rh = {tree[--r], rh};
        }
        return {lh, rh};
    }
}

using namespace SegmentTree;