#include "persistent-array.cpp"

// Q: maximum number of push_front/push_back operations, known offline
template<class T, int Q = 100000>
struct PersistentDeque {
    // defining state of some version of the deque
    int l, r;
    void *root;

    // constructor defaults to an empty deque
    PersistentDeque (void* root = nullptr, int l = 0, int r = -1)
        : root(root), l(l), r(r)
    {}

    bool empty () { return r < l; }
    int size () { return r - l + 1; }

    // updating array in O(lg M)
    PersistentDeque at (int i, const T& x) {
        // assert(i >= 0 && l + i <= r);
        return {update(root,-Q, Q - 1, i, x), l, r};
    }
    PersistentDeque pb (const T& x) {
        return {update(root, -Q, Q - 1, r + 1, new T(x)), l, r + 1};
    }
    PersistentDeque pop_back () {
        // assert(!empty());
        return {root, l, r - 1};
    }
    PersistentDeque push_front (const T& x) {
        return {update(root, -Q, Q - 1, l - 1, new T(x)), l - 1, r};
    }
    PersistentDeque pop_front () {
        // assert(!empty());
        return {root, l + 1, r};
    }

    // querying positions in O(lg M)
    T operator[] (int i) {
        // assert(i >= 0 && l + i <= r);
        return *((T*)query(root, -Q, Q - 1, i + l));
    }
    T front () {
        // assert(!empty());
        return *((T*)query(root, -Q, Q - 1, l));
    }
    T back () {
        // assert(!empty());
        return *((T*)query(root, -Q, Q - 1, r));
    }
};