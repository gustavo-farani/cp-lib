#include "dinic.cpp"
// also compatible with "edmonds-karp.cpp"
// (which is less efficient but easier to code than dinic)

struct BipartiteGraph {
    int n, m;
    FlowNetwork g;
    BipartiteGraph (int n, int m) : n(n), m(m), g(n + m + 2, 0) {
        for (int i = 0; i < n; i++) g.addArc(0, i + 2, 1);
        for (int i = 0; i < m; i++) g.addArc(i + n + 2, 1, 1);
    }
    // linearizing the indices
    // i: [0, n), index of a vertice from the left half 
    int left (int i) { return i + 2; }
    // j: [0, m), index of a vertice from the right half
    int right (int i) { return i + n + 2; }
    // binds the ith vertice of the left half
    // to the jth vertice of the right half
    void addEdge (int i, int j) {
        g.addArc(left(i), right(j), 1);
    }
    // returns a list of {{i, j}, k}, describing the edges
    // of a maximum cardinality matching
    // k: index of the represented edge (edges are numbered
    // from zero, in the order they appear in the input)
    // i: index of the vertex from the left half
    // j: index of the vertex from the right half
    vector<pair<ii, int>> maxMatching () {
        // 'cnt' will be holding the cardinality of
        // the maximum matching
        int cnt = g.maxFlow(0, 1);
        vector<pair<ii, int>> ans;
        for (int i = n + m << 1; i < g.e.size(); i += 2) {
            if (g.e[i].res() == 0) {
                ans.pb({{g.e[i + 1].to - 2, g.e[i].to - n - 2}, i >> 1});
            }
        }
        return ans;
    }
    // returns l and r, respectively listing the indices
    // of vertices on the left and right half
    // included in the minimum vertex cover
    pair<vi, vi> minVertexCover () {
        // 'cnt' will be holding the cardinality of
        // the minimum vertex cover
        int cnt = g.maxFlow(0, 1);
        vi l, r;
        for (int i = 0; i < n; i++) {
            if (g.cut(left(i))) l.pb(i);
        }
        for (int i = 0; i < m; i++) {
            if (!g.cut(right(i))) r.pb(i);
        }
        return {l, r};
    }
    // returns l and r, respectively listing the indices
    // of vertices on the left and right half
    // included in the maximum independent set
    pair<vi, vi> maxIndependentSet () {
        // 'cnt' will be holding the cardinality of
        // the maximum independent set
        int cnt = n + m - g.maxFlow(0, 1);
        vi l, r;
        for (int i = 0; i < n; i++) {
            if (!g.cut(left(i))) l.pb(i);
        }
        for (int i = 0; i < m; i++) {
            if (g.cut(right(i))) r.pb(i);
        }
        return {l, r};
    }
};