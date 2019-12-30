#include <vector>
using namespace std;

typedef long long ll;

struct RangeSum {
    vector<ll> bit;
    int n;
    RangeSum (int n) :
        bit(n + 1, 0),
        n(n)
    {}
    int lso (int i) {
        return (i & (-i));
    }
    void update (int i, ll delta) {
        for (int j = i; j <= n; j += lso(j)) {
            bit[j] += delta;
        }
    }
    ll query (int i) {
        ll sum = 0;
        for (int j = i; j > 0; j -= lso(j)) {
            sum += bit[j];
        }
        return sum;
    }
    ll range (int l, int r) {
        return query(r) - query(l - 1);
    }
};