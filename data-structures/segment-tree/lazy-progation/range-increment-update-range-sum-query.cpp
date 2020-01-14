typedef long long ll;

struct Node {
    ll sum;
    Node operator+ (const Node& o) {
        return Node{sum + o.sum};
    }
    void assign (ll x, int l, int r) {
        sum += x * (r - l + 1);
    }
} NIL{0};

struct Todo {
    ll add;
    ll top () { return add; }
    void push (ll x) { add += x; }
    bool empty () { return (add == 0); }
    void pop () { add = 0; }
};