#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef vector<int> vi;
typedef long long ll;

struct UE {      // Unweighted Edge
    int from, to;
};

struct WE {      // Weighted Edge
    int from, to;
    ll weigth;
    bool operator< (const WE& o) const {
        return weigth < o.weigth;
    }
};

template<class T>  // T: type of edge
struct Graph {
    int first, last, n;
    vector<T> e;
    vector<vi> adj;
    // base == 0: vertices indices in range [0, n)
    // base == 1: vertices indices in range [1, n]
    Graph (int n, bool base) :
        first(base), last(n + base), n(n), adj(last)
    {}
    void addEdge (const T& edge) {
        int z = e.size();   // 0-based indexation for edges
        adj[edge.from].pb(z);
        adj[edge.to].pb(z);
        e.pb(edge);
    }
};