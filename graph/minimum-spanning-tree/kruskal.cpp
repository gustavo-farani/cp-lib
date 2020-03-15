#include <tuple>
#include <vector>
#include <algorithm>
#include "../../data-structures/disjoint-sets-union/connection-test.cpp"
#include "../default/graph.cpp"
using namespace std;

#define pb push_back

// edges: possibly not a connected graph in edge list representation
vector<WE> minimumSpanningTree (const vector<WE>& edges) {
    int n = edges.size();
    vector<WE> mst;
    DSU dsu(n);
    sort(edges.begin(), edges.end(),
    [] (const WE& a, const WE& b) { return a.weigth < b.weigth; });
    for (const WE& e : edges) {
        if (!dsu.connected(e.from, e.to)) {
            mst.pb(e);
            dsu.merge(e.from, e.to);
        }
    }
    if (mst.size() == n - 1) return mst;
    else throw -1;             // detects a non-connected graph
}