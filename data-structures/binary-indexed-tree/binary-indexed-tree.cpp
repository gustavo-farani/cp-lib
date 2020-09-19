#include "../../boilerplate.cpp"

template<class T>
struct BIT {
    int n;
    vector<T> bit;
    BIT (int n) : n(n), bit(n + 1) {}
    int lso (int i) { return i & -i; }
    void update (int i, T x) {
        for (int j = i; j <= n; j += lso(j)) bit[j] += x;
    }
    T prefix (int i) {
        T sum = 0;
        for (int j = i; j > 0; j -= lso(j)) sum += bit[j];
        return sum;
    }
};