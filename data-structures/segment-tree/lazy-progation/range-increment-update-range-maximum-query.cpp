#include <algorithm>
using namespace std;

typedef long long ll;

struct Node {
    ll val;
    Node operator+ (const Node &o) {
        return Node{max(val, o.val)};
    }
    void assign (ll x) {
        val += x;
    }
} NIL{0};

struct Todo {
    ll add;
    bool empty () {return (add == 0); }
    void pop () { add = 0; }
    void push (ll x) { add += x; }
    ll top () { return add; }
};