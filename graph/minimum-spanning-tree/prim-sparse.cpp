#include <vector>
#include <tuple>
#include <queue>
using namespace std;

#define pb push_back
typedef pair<int, int> ii;
typedef pair<int, ii> iii;

struct Graph {       
    int n;                       // possibly not connected graph
    vector< vector<ii> > adj;    // weighted adjacency list
    Graph (int n) :              // 1-based
        n(n), adj(n + 1)
    {}
    void addEdge (int u, int v, int w) {
        adj[u].pb({w, v});      // undirected
        adj[v].pb({w, u});
    }
    vector<iii> minimumSpanningTree () {  // Prim's Algotrithm
        vector<iii> mst;        // MST is represented via edge list
        vector<bool> taken(n + 1);
        priority_queue < iii, vector<iii>, greater<iii> > margin;
        int u = 1, v, w;
        while (mst.size() < n - 1) {
            taken[u] = true;
            for (ii &e : adj[u]) {
                tie (w, v) = e;
                if (!taken[v]) margin.push({w, {v, u}});
            }
            do {
                if (margin.empty()) {
                    throw -1;  // not a connected graph
                } else {
                    w = margin.top().first;
                    tie (u, v) = margin.top().second;
                    margin.pop();
                }
            } while (taken[u] && taken[v]);
            mst.pb({w, {u, v}});
        }
        return mst;
    }
};