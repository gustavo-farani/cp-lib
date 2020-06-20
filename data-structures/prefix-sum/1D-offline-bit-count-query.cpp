#include "../../template.cpp"

struct BitCount {
    vi sum;
    BitCount (int n, bool base) : sum(n + base) {}
    void build () { partial_sum(sum.begin(), sum.end()); }
    int count (int l, int r) {
    	return l == 0 ? sum[r] : sum[r] - sum[l - 1];
    }
    bool all (int l, int r) { return count(l, r) == r - l + 1; }
    bool any (int l, int r) { return count(l, r) > 0; }
    bool none (int l, int r) { return count(l, r) == 0; }
};
