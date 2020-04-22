#include "../../template.cpp"

#define x first
#define y second

// cardinal points: {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}
// intercardinal points: {{1, -1}, {-1, -1}, {-1, 1}, {1, 1}}
vector<ii> windrose({{1, 0}, {0, 1}, {-1, 0}, {0, -1}});

struct Grid {
    vector<vector<bool>> pass;  // if passable
    vector<vi> dist;
    Grid (int n, int m) :
        pass(n + 2, vector<bool>(m + 2, false)),
        dist(n + 2, vi(m + 2, INT_MAX))
    {}
    void minimumDistances (const ii &s) {   // Single-Source Breadth-First-Search
        queue<ii> q;
        dist[s.x][s.y] = 0;
        q.push(s);
        while (!q.empty()) {
            ii &u = q.front();
            for (ii &d : windrose) {
                ii v(u.x + d.x, u.y + d.y);
                if (pass[v.x][v.y] && dist[v.x][v.y] == INT_MAX) {
                    dist[v.x][v.y] = 1 + dist[u.x][u.y];
                    q.push(v);
                }
            }
            q.pop();
        }
    }
    void minimumDistances (const vector<ii> &s) {  // Multi-Source Breadth-First-Search
        queue<ii> q;
        for (ii u : s) {
            dist[u.x][u.y] = 0;
            q.push(u);
        }
        while (!q.empty()) {
            ii &u = q.front();
            for (ii &d : windrose) {
                ii v(u.x + d.x, u.y + d.y);
                if (pass[v.x][v.y] && dist[v.x][v.y] == INT_MAX) {
                    dist[v.x][v.y] = 1 + dist[u.x][u.y];
                    q.push(u);
                }
            }
            q.pop();
        }
    }
};