#include "../../template.cpp"

// same functionality as regular DSU,
// but stores data in maps, instead of arrays
// space complexity gets better, but time complexity gets worse
struct DSU {
    int n;
    map<int, int> par, sz;
    DSU (int n) : n(n) {}
    int find (int u) {
        auto it = par.lower_bound(u);
        if (it == par.end() || it->first != u) {
            it = par.emplace_hint(it, u, u);
        } else if (it->second != u) {
            it->second = find(it->second);
        }
        return it->second;
    }
    int& size (int u) {
        auto it = sz.lower_bound(u);
        if (it == sz.end() || it->first != u) {
            it = sz.emplace_hint(it, u, 1);
        }
        return it->second;
    }
    void merge (int u, int v) {
        u = find(u), v = find(v);
        if (u != v) {
            n--;
            int& x = size(u), y = size(v);
            if (x < y) {
                par[u] = v;
                y += x;
            } else {
                par[v] = u;
                x += y;
            }
        }
    }
    void swap (DSU& o) {
        std::swap(n, o.n);
        par.swap(o.par);
        sz.swap(o.sz);
    }
    int size () {
        return par.size();
    }
};