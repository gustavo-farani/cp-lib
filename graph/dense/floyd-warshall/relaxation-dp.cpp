#include "../representation/dense-graph.cpp"

// computes minimum distances, gradually relaxing the restriction
// on what vertices can be used as intermediates on shortest paths
// p: a permutation of the vertex indices
// dp[i][u][v]: minimum distance from u to v using only vertices
// p[0], p[1], ..., p[i] as intermediates
// the source vertex and the destination vertex of a shortest path
// are never considered intermediate
template<class T>
vector<vector<vector<T>>> Graph<T>::relaxation (const vi& p) {
    vector<vector<vector<T>>> dp;
    auto prev = adj;
    for (int mid : p) {
        auto cur = adj;
        for (int u = first; u < last; u++) {
            for (int v = first; v < last; v++) {
                cur[u][v] = min(prev[u][v], prev[u][mid] + prev[mid][v]);
            }
        }
        dp.pb(cur);
        prev.swap(cur);
    }
    return dp;
}