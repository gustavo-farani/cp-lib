#include <algorithm>
using namespace std;

typedef long long ll;
const ll INF = 1e9;

struct Node {
    ll sum, llocal, rlocal, global;
    Node operator+ (Node o) {
        if (global == -INF) {
            return Node{o};
        } else if (o.global == -INF) {
            return *this;
        } else {
            return Node{
                sum + o.sum,
                max(llocal, sum + o.llocal),
                max(o.rlocal, o.sum + rlocal),
                max({global, o.global, rlocal + o.llocal})
            };
        }
    }
    void leaf (ll x) {
        sum = llocal = rlocal = global = x;
    }
} NIL{-INF, -INF, -INF, -INF};