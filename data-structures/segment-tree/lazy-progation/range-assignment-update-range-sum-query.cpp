typedef long long ll;

struct Node {
    ll sum;
    Node operator+ (const Node &o) {
        return Node{sum + o.sum};
    }
    void assign (int x, int l, int r) {
        sum = (ll) x * (r - l + 1);
    }
} NIL{0};

struct Todo {
    bool status;
    int val;
    bool empty () { return !status; }
    void pop () { status = false; }
    void push (int x) {
        status = true;
        val = x;
    }
    int top () { return val; }
};