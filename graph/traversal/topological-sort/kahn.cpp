#include <vector>
#include <queue>
using namespace std;

#define pb push_back
typedef vector<int> vi;

struct DAG {
    int n;
    vector<vi> adj;   // outgoing unweighted adjacency list
    vi deg;   // incoming degree
    DAG (int n) :
        n(n),
        adj(n + 1),   // 1-based
        deg(n + 1)
    {}
    void addEdge (int u, int v) {
        adj[u].pb(v);
        deg[v]++;
    }
    vi toposort () {   // Kahn's iterative (BFS like) algorithm
        vi ts;
        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (deg[i] == 0) q.push(i);
        }
        while (ts.size() < n) {
            if (q.empty()) {
                throw -1;    // cyclic graph (not a DAG)
            } else {
                int u = q.front();
                q.pop();
                ts.pb(u);
                for (int v : adj[u]) {
                    if (--deg[v] == 0) {
                        q.push(v);
                    }
                }
            }
        }
        return ts;
    }
};