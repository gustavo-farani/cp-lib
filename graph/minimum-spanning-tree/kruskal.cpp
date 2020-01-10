#include <tuple>
#include <vector>
#include <algorithm>
#include "../../data-structures/disjoint-sets-union.cpp"
using namespace std;

#define pb push_back
typedef pair< int, pair<int, int> > iii;

struct Graph {      // possibly not connected graph
    int n;
    vector<iii> edges;    // weighted edge list
    Graph (int n) : n(n) {}
    void addEdge (int u, int v, int w) {
        edges.pb({w, {u, v}});  // undirected
    }
    vector<iii> minimumSpanningTree () { // Kruskal's Algorithm
        vector<iii> mst;
        DSU forest(n);
        sort(edges.begin(), edges.end());
        for (iii &e : edges) {
            int u, v;
            tie (u, v) = e.second;
            if (!forest.tied(u, v)) {
                mst.pb(e);
                forest.merge(u, v);
            }
        }
        if (mst.size() == n - 1) {
            return mst;
        } else {
            throw -1;    // not a connected graph
        }
    }
};