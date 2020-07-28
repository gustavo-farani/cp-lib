#include "../../boilerplate.cpp"

// n: integer >= 0
// return: vector containing pairs representing ranges [l, r],
// 1 <= l <= r <= n, such that, for each l <= i <= r,
// floor(n/i) always yields the same > 0 value
// NOTE: for n == 0, it returns an empty vector
vector<ii> floorEqualRanges (int n) {
    vector<ii> ans;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = n/(n/l);
        ans.emplace_back(l, r);
    }
    return ans;
}

// n: integer >= 0
// return: vector containing pairs representing ranges [l, r],
// 1 <= l <= r < n, such that, for each l <= i <= r,
// floor(n/i) always yields the same > 1 value
// NOTE: for n == 0 or n == 1, it returns an empty vector
vector<ii> ceilEqualRanges (int n) {
    return floorEqualRanges(n - 1);
}