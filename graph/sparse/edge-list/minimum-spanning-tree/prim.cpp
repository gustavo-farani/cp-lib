#include "../representation/graph.cpp"

// g: possibly not connected weighted graph
// in edge list representation
// return: indices of g's edges which compose a MST, 
// if g is connected
// raises exception if the graph is disconnected
vi minimumSpanningTree (const Graph<WE>& g) {
    vi mst;
    vector<bool> taken(g.last);
    priority_queue<int, vi, function<bool(int, int)>>
    pq([&] (int i, int j) { return g.e[j] < g.e[i]; });
    int u = g.first, v;
    while (mst.size() < g.n - 1) {
        taken[u] = true;
        for (int z : g.adj[u]) {
            int v = u ^ g.e[z].from ^ g.e[z].to;
            if (!taken[v]) pq.push(z);
        }
        int z;
        do {
            if (pq.empty()) throw -1;  // disconnected
            else {
                z = pq.top(), pq.pop();
                u = g.e[z].from, v = g.e[z].to;
            }
        } while (taken[u] && taken[v]);
        mst.pb(z);
        if (taken[u]) u = v;
    }
    return mst;
}