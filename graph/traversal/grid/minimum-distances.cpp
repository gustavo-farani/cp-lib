#include <vector>
#include <tuple>
#include <queue>
using namespace std;

#define pb push_back
#define x first
#define y second
typedef pair<int, int> ii;
typedef vector<int> vi;

const int INF = 0x3f3f3f3f;

// cardinal points: {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}
// intercardinal points: {{1, -1}, {-1, -1}, {-1, 1}, {1, 1}}
vector<ii> windrose({{1, 0}, {0, 1}, {-1, 0}, {0, -1}});

struct Grid {
    int n, m;
    vector< vector<bool> > pass;  // if passable
    vector<vi> dist;
    Grid (int n, int m) :
        n(n),
        m(m),
        pass(n + 2, vector<bool>(m + 2, false)),
        dist(n + 2, vi(m + 2, INF))
    {}
    void bfs (const ii &src) {   // Single-source
        queue<ii> q;
        dist[src.x][src.y] = 0;
        q.push(src);
        while (!q.empty()) {
            ii &v = q.front();
            for (ii &d : windrose) {
                ii u(v.x + d.x, v.y + d.y);
                if (pass[u.x][u.y] && dist[u.x][u.y] == -1) {
                    dist[u.x][u.y] = 1 + dist[v.x][v.y];
                    q.push(u);
                }
            }
            q.pop();
        }
    }
    void bfs (const vector<ii> &s) {  // Multi-source
        queue<ii> q;
        for (ii src : s) {
            dist[src.x][src.y] = 0;
            q.push(src);
        }
        while (!q.empty()) {
            ii &v = q.front();
            for (ii &d : windrose) {
                ii u(v.x + d.x, v.y + d.y);
                if (pass[u.x][u.y] && dist[u.x][u.y] == INF) {
                    dist[u.x][u.y] = 1 + dist[v.x][v.y];
                    q.push(u);
                }
            }
            q.pop();
        }
    }
};