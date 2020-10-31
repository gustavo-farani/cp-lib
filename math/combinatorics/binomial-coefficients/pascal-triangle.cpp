#include "../mod-base.cpp"

// dp[n][k] := number of subsets with
// exactly k elements from a set with n elements
// time complexity: O(N^2)
// no divisions are necessary

const int N = 1e3;

MB dp[N + 1][N + 1];

void build () {
    for (int n = 0; n <= N; n++) {
        dp[n][0] = dp[n][n] = 1;
        for (int k = 1; k < N; k++) {
            dp[n][k] = dp[n - 1][k] + dp[n - 1][k - 1];
        }
    }
}