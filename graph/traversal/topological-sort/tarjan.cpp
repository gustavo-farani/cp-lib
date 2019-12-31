#include <vector>
#include <deque>
using namespace std;

#define pb push_back
typedef vector<int> vi;

struct DAG {   // Directed Acyclic Graph
    int n;
    vector<vi> adj;
    vi c;
    deque<int> ts;  // std::deque is used instead of std::vector
    // beacuse the latter doesn't support push_front()
    DAG (int n) :
        n(n),
        adj(n + 1),   // 1-based
        c(n + 1)
    {}
    void addEdge (int u, int v) { adj[u].pb(v); }
    deque<int> toposort () {
        for (int i = 1; i <= n; i++) {   // 1-based
            if (c[i] == 0) dfs(i);
        }
        return ts;
    }
    void dfs (int u) {
        c[u] = 1;
        for (int v : adj[u]) {
            if (c[v] == 0) {
                dfs(v);
            } else if (c[v] == 1) {
                throw -1;   // detected cycle (not a DAG)
            }
        }
        c[u] = 2;
        ts.push_front(u);
    }
};