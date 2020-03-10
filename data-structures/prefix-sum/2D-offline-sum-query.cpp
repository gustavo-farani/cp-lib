#include <vector>
using namespace std;

template<class T>
struct PrefixSum2D {
    vector< vector<T> > p;
    PrefixSum2D (int n, int m) : p(n + 1, vector<T>(m + 1)) {}
    T& at (int i, int j) { return p[i][j]; }      // 1-based indexation
    void build (int n, int m) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                p[i][j] += p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1];
            }
        }
    }
    T query (int r1, int c1, int r2, int c2) {    // 1-based indexation, closed interval
        return (p[r2][c2] + p[r1 - 1][c1 - 1]) - (p[r2][c1 - 1] + p[r1 - 1][c2]);
    }
};