#include "../mod-base.cpp"

struct PascalTriangle {
    vector<vector<MB>> memo;
    PascalTriangle (int n) : memo(n + 1, vector<MB>(n + 1, -1)) {}
    MB operator() (int n, int k) {
        MB& ans = memo[n][k];
        if (ans == -1) {
            if (k == 0 || k == n) ans = 1;
            else ans = operator()(n - 1, k) + operator()(n - 1, k - 1);
        }
        return ans;
    }
} combinations(1e3);