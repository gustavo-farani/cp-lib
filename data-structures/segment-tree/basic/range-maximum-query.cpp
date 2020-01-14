#include <algorithm>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

struct Node {
    ll val;
    Node operator+ (Node o) {
        return Node{max(val, o.val)};
    }
    void leaf (ll x) { val = x; }
} NIL{-INF};