#include "transitive-closure.cpp"

// p: partition of the vertex set into SCC's as a vector of vectors,
// each vector containing the indices of vertices part of the same SCC
// id[u] := index of the SCC vertex u is part of; two vertices u and v
// will lie in the same strongly connected component iff id[u] == id[v]
// return: number of SCC's in the graph
// complexity: O(N^3)
int Graph::stronglyConnectedComponents (vector<vi>& p) {
    auto r = transitiveClosure();
    vi id(last, -1);
    int cnt = 0;
    for (int u = first; u < last; u++) {
        if (id[u] != -1) continue;
        vi c({u});
        id[u] = cnt++;
        for (int v = u + 1; v < last; v++) {
            if (r[u][v] && r[v][u]) {
                id[v] = id[u];
                c.pb(v);
            }
        }
        p.pb(c);
    }
    return cnt;
}