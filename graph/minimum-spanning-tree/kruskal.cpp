#include <tuple>
#include <vector>
#include <algorithm>
#include "../../data-structures/disjoint-sets-union.cpp"
using namespace std;

#define pb push_back
typedef pair< int, pair<int, int> > iii;

struct Graph {      // connected undirected weighted graph
    int n;
    vector<iii> edges;
    Graph (int n) : n(n) {}
    void addEdge (int u, int v, int w) {
        edges.pb({w, {u, v}});
    }
    vector<iii> minimumSpanningTree () { // returns MST in edge list representation
        vector<iii> mst;
        DSU forest(n);
        sort(edges.begin(), edges.end());
        for (int i = 0; mst.size() < n - 1; i++) {
            int u, v;
            tie (u, v) = edges[i].second;
            if (!forest.tied(u, v)) {
                mst.pb(edges[i]);
                forest.merge(u, v);
            }
        }
        return mst;
    }
};