#include "../../boilerplate.cpp"

// cardinal points: {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}
// intercardinal points: {{1, -1}, {-1, -1}, {-1, 1}, {1, 1}}
const vector<ii> windrose({{1, 0}, {0, 1}, {-1, 0}, {0, -1}});

struct Grid {
    vector<vi> g, dist;
    Grid (int n, int m) :
        g(n + 2, vi(m + 2)), dist(n + 2, vi(m + 2))
    {}
    int& at (int i, int j) { return g[i][j]; }
    // Single-Source Breadth-First-Search
    vector<vi>& minimumDistances (int si, int sj) {
        for (vi& a : dist) fill(a.begin(), a.end(), INT_MAX);
        queue<ii> q;
        dist[si][sj] = 0;
        q.emplace(si, sj);
        while (!q.empty()) {
            auto [ui, uj] = q.front();  // C++ 17 only
            q.pop();
            for (const ii &d : windrose) {
                int vi = ui + d.fi, vj = uj + d.se;
                if (g[vi][vj] && dist[vi][vj] == INT_MAX) {
                    dist[vi][vj] = 1 + dist[ui][uj];
                    q.emplace(vi, vj);
                }
            }
        }
        return dist;
    }
    // Multi-Source Breadth-First-Search
    vector<vi>& minimumDistances (const vector<ii> &s) {
        for (vi& a : dist) fill(a.begin(), a.end(), INT_MAX);
        queue<ii> q;
        for (auto [si, sj] : s) {  // C++ 17 only
            dist[si][sj] = 0;
            q.emplace(si, sj);
        }
        while (!q.empty()) {
            auto [ui, uj] = q.front();  // C++ 17 only
            q.pop();
            for (const ii &d : windrose) {
                int vi = ui + d.fi, vj = uj + d.se;
                if (g[vi][vj] && dist[vi][vj] == INT_MAX) {
                    dist[vi][vj] = 1 + dist[ui][uj];
                    q.emplace(vi, vj);
                }
            }
        }
        return dist;
    }
};