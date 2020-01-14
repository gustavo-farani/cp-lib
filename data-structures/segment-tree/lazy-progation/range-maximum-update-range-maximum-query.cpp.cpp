#include <algorithm>
using namespace std;

struct Node {
    int y;
    Node operator+ (const Node &o) {
        return Node{max(y, o.y)};
    }
    void assign (int x) {
        y = max(y, x);
    }
} NIL{0};

struct Todo {
    int y;
    bool empty () { return (y == 0); }
    void pop () { y = 0; }
    void push (int x) { y = max(y, x); }
    int top () { return y; }
};