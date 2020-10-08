#include "../representation/graph.cpp"
#include "../representation/weighted-edge.cpp"

// g: possibly not connected weighted graph
// in edge list representation
// return: pointers to g's edges which compose a MST, 
// if g is connected
// throws an exception if the graph is disconnected
vector<Edge*> minimumSpanningTree (const Graph& g) {
    vector<Edge*> mst;
    vector<bool> taken(g.last);
    priority_queue<Edge*, vector<Edge*>, function<bool(Edge*, Edge*)>>
    pq([&] (Edge* e1, Edge* e2) { return *e2 < *e1; });
    int u = g.first, v;
    while (mst.size() < g.n - 1) {
        taken[u] = true;
        for (auto e : g.adj[u]) {
            v = e->other(u);
            if (!taken[v]) pq.push(e);
        }
        Edge* e;
        do {
            if (pq.empty()) {
                throw -1;  // disconnected
            } else {
                e = pq.top();
                pq.pop();
                u = e->from;
                v = e->to;
            }
        } while (taken[u] && taken[v]);
        mst.pb(e);
        if (taken[u]) u = v;
    }
    return mst;
}