#include <vector>
#include <tuple>
using namespace std;

#define pb push_back
#define x first
#define y second
typedef pair<int, int> ii;
typedef vector<int> vi;
 
// cardinal points: {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}
// intercardinal points: {{1, -1}, {-1, -1}, {-1, 1}, {1, 1}}
vector<ii> windrose({{1, 0}, {0, 1}, {-1, 0}, {0, -1}});
 
struct Grid {
    int n, m;
    vector<vector<bool>> e;  // zero-one matrix representing the input grid
    // 1 - passable, 0 - impassable
    vector<vi> c;  // c[i][j]: color of cell at coordinates i and j, i.e.,
    // the numeric label identifying the connected component cell (i, j) is part of
    vi sz;   // sz[i]: size (number of connected cells) of the component with color i
    Grid (int n, int m) :
        n(n),
        m(m),
        e(n + 2, vector<bool>(m + 2, false)),  // one-based indexation for rows and columns
        // matrix e is supposed to be manually read: the constructor only resets every bit by default
        c(n + 2, vi(m + 2, -1)),     // -1 label for unvisited cells
        sz(1)   // the connected components indexation is one-based
        // 0 doesn't stems for a valid component label
    {}
    void dfs (const ii &v, int lb) {   // flood-fill (dfs coloring) recursive method
        if (e[v.x][v.y]) {
            c[v.x][v.y] = lb;
            sz[lb]++;
            for (const ii &d : windrose) {
                ii u(v.x + d.x, v.y + d.y);
                if (c[u.x][u.y] == -1) {
                    dfs(u, lb);
                }
            }
        } else {
            c[v.x][v.y] = 0;
        }
    }
    int count (const ii &v) {   // if v iterates through all the cells of the grid,
    // the size of each cell's component is determined amortizedly in O(N*M)
        if (c[v.x][v.y] == -1) {
            int lb = sz.size();
            sz.pb(0);
            dfs(v, lb);
        }
        return sz[c[v.x][v.y]];
    }
};