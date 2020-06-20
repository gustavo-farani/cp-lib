#include "../../template.cpp"

template<class T>
struct RangeIncrement {
    vector<T> sum;
    RangeIncrement (int n, bool base) : sum(n + 1 + base) {}
    void update (int l, int r, T x) {
        sum[l] += x;
        sum[r + 1] -= x;
    }
    void build () {
        partial_sum(sum.begin(), sum.end(), sum.begin());
        partial_sum(sum.begin(), sum.end(), sum.begin());
    }
    T query (int l, int r) {
        return l == 0 ? sum[r] : sum[r] - sum[l - 1];
    }
};
