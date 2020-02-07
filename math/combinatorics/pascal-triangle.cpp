#include <vector>
#include "../util/mod-base.cpp"
using namespace std;

#define pb push_back

struct PascalTriangle {
    vector< vector<ModBase> > memo;
    PascalTriangle (int n) {
        for (int i = 0; i <= n; i++) {
            memo.pb(vector<ModBase>(n + 1, ModBase(-1)));
        }
    }
    ModBase operator() (int n, int k) {
        ModBase& ans = memo[n][k];
        if (ans.val == -1) {
            if (k == 0 || k == n) {
                ans.val = 1;
            } else {
                ans = operator()(n - 1, k) + operator()(n - 1, k - 1);
            }
        }
        return ans;
    }
} combinations(1e3);