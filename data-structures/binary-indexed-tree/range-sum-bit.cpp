#include <vector>
using namespace std;

typedef long long ll;

template <typename T>
struct RangeSum {
    vector<T> bit;
    int n;
    RangeSum (int n) :
        bit(n + 1, 0),
        n(n)
    {}
    int lso (int i) {
        return (i & (-i));
    }
    void update (int i, T delta) {
        for (int j = i; j <= n; j += lso(j)) {
            bit[j] += delta;
        }
    }
    T query (int i) {
        T sum = 0;
        for (int j = i; j > 0; j -= lso(j)) {
            sum += bit[j];
        }
        return sum;
    }
    T range (int l, int r) {
        return query(r) - query(l - 1);
    }
};