#include "../../../template.cpp"

struct Node {
    ll val;
    Node operator+ (Node o) {
        return Node{min(val, o.val)};
    }
    void leaf (ll x) { val = x; }
} NIL{LLONG_MAX};