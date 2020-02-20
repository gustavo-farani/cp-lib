#include <vector>
using namespace std;

template<class T>
struct PrefixSum2D {
    vector< vector<T> > p;
    PrefixSum2D (int n, int m) : p(n + 1, vector<T>(m + 1)) {}
    T& at (int i, int j) {    // 1-based indexation
        return p[i][j];
    }
    void build (int n, int m) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                p[i][j] += p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1];
            }
        }
    }
    T query (int i1, int j1, int i2, int j2) { // 1-based indexation, closed interval
        return (p[i2][j2] + p[i1 - 1][j1 - 1]) - (p[i2][j1 - 1] + p[i1 - 1][j2]);
    }
};