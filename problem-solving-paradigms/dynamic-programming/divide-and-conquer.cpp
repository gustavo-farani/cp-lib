#include "../../boilerplate.cpp"
#include "../two-pointers/sliding-window.cpp"

const int N = 1e4;  // TODO set maximum array size

bool pre, cur;  // for memory compression
ll dp[2][N];

// TODO cost of taking subarray [l, r] as a block
inline ll cost(int l, int r) {
    return TwoPointers::query(l, r);
}

void solve (int l, int r, int pl, int pr) {
    if (r < l) return;
    int m = l + r >> 1;
    pair<ll, int> opt;
    // NOTE: objective function is maximized
    opt.first = numeric_limits<ll>::min();
    for (int i = pl; i <= pr; i++) {
        if (i > m) break;
        // NOTE: objective function is maximized
        opt = max(opt, {dp[pre][i - 1] + cost(i, m), i});
    }
    dp[cur][m] = opt.first;
    solve(l, m - 1, pl, opt.second);
    solve(m + 1, r, opt.second, pr);
}

// n: array size
// k: exact number of blocks for the partition
// time complexity: O(k*n*lg n)
ll solve (int n, int k) {
    TwoPointers::init();
    cur = 0, pre = 1;
    // NOTE: 0-based indexation for array indices
    for (int i = 0; i < n; i++) dp[cur][i] = cost(0, i);
    for (int i = 1; i < k; i++) {
        swap(cur, pre);
        solve(i, n - 1, i, n - 1);
    }
    return dp[cur][n - 1];
}