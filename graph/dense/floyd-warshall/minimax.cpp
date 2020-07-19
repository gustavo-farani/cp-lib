#include "../representation/dense-graph.cpp"

// mima[u][v]: minimum possible value
// of a maximum edge weigth on a path from u to v
template<class T>
vector<vector<T>> Graph<T>::minimax () {
    // remove reference only if necessary to keep original edge weights
    auto& mima = adj;
    for (int mid = first; mid < last; mid++) {
        for (int u = first; u < last; u++) {
            for (int v = first; v < last; v++) {
                mima[u][v] = mima(dist[u][v], max(mima[u][mid], mima[mid][v])); 
            }
        }
    }
    return mima;
}