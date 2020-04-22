#include "../../../template.cpp"

struct Node {
    ll val;
    Node operator+ (Node o) {
        return Node{max(val, o.val)};
    }
    void leaf (ll x) { val = x; }
} NIL{LLONG_MIN};