#include "../representation/weighted-graph.cpp"

struct SubTree {
    // TODO default initialization must already
    // handle the insertion of the root node
    SubTree () {}
    // TODO determine the smaller component, which will be
    // the faster one for iterating through its vertices
    bool operator< (const SubTree& o) {}
    // TODO iterate through *this (small) component,
    // and count how many valid paths are there
    // with starting vertices from *this component and
    // terminal vertices from the large component,
    // crossing an edge with weight w in between
    ll count (int w, SubTree& large) {}
    // TODO iterate through the small component,
    // aggregating its paths into *this (large) component
    void merge (SubTree& small) {}
    // an edge with weight w is appended to all the paths
    void update (int w) {}
};

// swapping in constant time
void swap (SubTree& lhs, SubTree& rhs) {}

SubTree dfs (Graph& g, int u, int par, ll& paths) {
    SubTree ans;
    for (auto [w, v] : g.adj[u]) {  // C++17 only
        if (v != par) {
            SubTree sub = dfs(g, v, u, paths);
            if (sub < ans) {
                paths += sub.count(w, ans);
                sub.update(w);
                ans.merge(sub);
            } else {
                paths += ans.count(w, sub);
                sub.update(w);
                swap(ans, sub);
                ans.merge(sub);
            }
        }
    }
    return ans;
}

// application: https://codeforces.com/gym/101856
// (problem E: Evaluations)