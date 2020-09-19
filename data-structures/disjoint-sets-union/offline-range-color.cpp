#include "../../boilerplate.cpp"

// TO BE TESTED

// B: base indexation
// B == 0: array indices in [0, n)
// B == 1: array indices in [1, n]
template<bool B>
struct RangeColor {  // Offline Range Color Update
    vi par, c;
    deque<tuple<int, int, int>> u;
    // all positions are initially set to color number 0
    RangeColor (int n) : par(n + B + 1), c(n + B) {
        iota(par.begin(), par.end(), 0);
    }
    // overwrites positions from l to r with color number x
    void update (int l, int r, int x) { u.emplace_front(l, r, x); }
    int find (int v) { return par[v] == v ? v : par[v] = find(par[v]); }
    // returns: final color at each position
    vi& solve () {
        for (auto [l, r, x] : u) {
            for (int i = find(l); i <= r; i = find(i)) {
                c[i] = x;
                par[i] = i + 1;
            }
        }
        return c;
    }
};