#include <vector>
using namespace std;

#define pb push_back
typedef vector<int> vi;
typedef pair< int, pair<int, int> > iii;

const int INF = 0x3f3f3f3f;

struct DenseGraph {
    int n;
    vector<vi> adj;
    DenseGraph (int n) :  // 0-based
        n(n), adj(n, vi(n, INF))
    {}
    void addEdge (int u, int v, int w) {
        adj[u][v] = adj[v][u] = w;
    }
    vector<iii> minimumSpanningTree () {
        vector<iii> mst;
        vector<bool> taken(n);   // 0-based
        vi nearest(n), dist(n, INF); // 0-based
        int u = 0, v;  // 0-based
        while (mst.size() < n - 1) {
            taken[u] = true;
            for (v = 0; v < n; v++) {  // 0-based
                if (adj[v][u] < dist[v]) {
                    dist[v] = adj[v][u];
                    nearest[v] = u;
                }
            }
            int w = INF;
            for (int i = 0; i < n; i++) { // 0-based
                if (!taken[i] && dist[i] < w) {
                    w = dist[i];
                    u = i;
                    v = nearest[i];
                }
            }
            mst.pb({w, {u, v}});
        }
        return mst;
    }
};