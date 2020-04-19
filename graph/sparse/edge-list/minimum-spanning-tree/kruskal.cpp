#include "../../data-structures/disjoint-sets-union/connection-test.cpp"
#include "../representation/graph.cpp"
using namespace std;

// g: possibly not connected weighted graph in edge list representation
// return: indices of g's edges which compose a MST, if g is connected
// raises exception if g is disconnected
vi minimumSpanningTree (const Graph<WE>& g) {
    vi mst, v(g.e.size());
    iota(v.begin(), v.end(), 0);
    sort(v.begin(), v.end(), [&] (int i, int j) { return g.e[i] < g.e[j]; });
    DSU dsu(g.last);
    for (int z : v) {
        if (!dsu.connected(g.e[z].from, g.e[z].to)) {
            mst.pb(z);
            dsu.merge(g.e[z].from, g.e[z].to);
        }
    }
    if (mst.size() == g.n - 1) return mst;
    else throw -1;
}