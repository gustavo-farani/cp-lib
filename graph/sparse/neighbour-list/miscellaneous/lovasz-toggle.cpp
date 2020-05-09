#include "../representation/unweighted-graph.cpp"

vector<bool> lovaszToggle (const Graph& g, const array<int, 2>& lim) {
    vector<bool> c(g.last);
    vi cnt(g.last);
    set<int> bad;
    for (int u = g.first; u < g.last; u++) {
        if ((cnt[u] = g.adj[u].size()) > lim[0]) bad.insert(u);
    }
    while (!bad.empty()) {
        auto it = bad.begin();
        int u = *it;
        bad.erase(it);
        for (int v : g.adj[u]) {
            if (c[v] == c[u]) {
                if (--cnt[v] == lim[c[v]]) bad.erase(v);
            } else {
                if (cnt[v]++ == lim[c[v]]) bad.insert(v);
            }
        }
        c[u] = !c[u];
        cnt[u] = g.adj[u].size() - cnt[u];
    }
    return c;
}