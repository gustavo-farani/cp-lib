#include "../../../../data-structures/disjoint-sets-union/connection-test.cpp"
#include "../representation/weighted-edge.cpp"

// edges: list of edges of a weighted graph
// n: number of vertices in the graph
// b: base indexation for vertices indices
// return: sum of edge weights of minimum spanning tree
// throw an exception if graph is disconnected
ll minimumSpanningTree (vector<Edge>& edges, int n, bool b) {
    ll sum = 0;
    int cnt = 0;
    sort(edges.begin(), edges.end());
    DSU dsu(n + b);
    for (Edge& e : edges) {
        if (!dsu.connected(e.from, e.to)) {
            // TODO edge e is part of the MST
            sum += e.weight;
            cnt++;
            dsu.merge(e.from, e.to);
        }
    }
    if (cnt == n - 1) return sum;
    else throw -1;
}