#include "../../boilerplate.cpp"

// same functionality as regular DSU,
// but stores data in maps, instead of arrays
// space complexity gets better, but time complexity gets worse
template<class T>
struct DSU {
    int n;
    map<T, T> par;
    map<T, int> sz;
    DSU (int n) : n(n) {}
    T find (T u) {
        auto it = par.lower_bound(u);
        if (it == par.end() || it->fi != u) {
            it = par.emplace_hint(it, u, u);
        } else if (it->se != u) {
            it->se = find(it->se);
        }
        return it->se;
    }
    int& size (T u) {
        auto it = sz.lower_bound(u);
        if (it == sz.end() || it->fi != u) {
            it = sz.emplace_hint(it, u, 1);
        }
        return it->se;
    }
    void merge (T u, T v) {
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
