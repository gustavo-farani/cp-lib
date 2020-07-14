#include "../representation/boolean-adjacency-matrix.cpp"

// computes the transitive closure of the directed graph
// r[u][v] == true iff v is reachable from u
// complexity: O(N^3)
vector<vector<bool>> Graph::transitiveClosure () {
    // remove reference only if necessary to keep original edge weights
    auto& r = adj;
    for (int mid = first; mid < last; mid++) {
        for (int u = first; u < last; u++) {
            for (int v = first; v < last; v++) {
                r[u][v] = r[u][v] || r[u][mid] && r[mid][v];
            }
        }
    }
    return r;
}