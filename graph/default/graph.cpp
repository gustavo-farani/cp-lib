#include <vector>
using namespace std;

#define pb push_back
typedef vector<int> vi;
typedef long long ll;

struct UE {      // Unweighted Edge
    int from, to;
};

struct WE {      // Weighted Edge
    int from, to;
    ll weigth;
};

template<class T>
struct Graph {
    int n;
    vector<T> edges;
    vector<vi> adj;
    Graph (int n) :
        n(n), adj(n + 1)        // 1-based indexation for nodes
    {}
    void link (const T& e) {
        int z = edges.size();   // 0-based indexation for edges
        adj[e.from].pb(z);
        adj[e.to].pb(z);
        edges.pb(e);
    }
};