#include "minimum-distances.cpp"

template<class T>
bool Graph<T>::hasNegativeCycle () {
    auto dist = minimumDistances();
    for (int u = first; u < last; u++) {
        if (dist[u][u] < 0) return true;
    }
    return false;
}