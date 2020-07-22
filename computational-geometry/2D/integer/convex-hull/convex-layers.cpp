#include "../point.cpp"

// "Onion Layers"
// Nested convex hulls of a set of points
// complexity: O(N^2)
vector<vector<PT>> convexLayers (const vector<PT>& v) {
    int cnt = 0, n = v.size();
    vector<bool> taken(n);
    vector<vector<PT>> layer;
    while (cnt < n) {
        vi t;
        for (int i = 0; i < n; i++) {
            if (!taken[i]) {
                t.pb(i);
                if (v[i] < v[t[0]]) {
                    swap(t.back(), t[0]);
                }
            }
        }
        sort(next(t.begin()), t.end(), [&] (int i, int j) {
            PT u = v[i] - v[t[0]], w = v[j] - v[t[0]];
            ll c = u % w;
            if (c == 0) {
            	return u.x == 0 ? w < u : u < w;
            } else {
                return c >= 0;
            }
        });
        vi h(t.size());
        int sz = 0;
        for (int i : t) {
            while (sz > 1 && (v[i] - v[h[sz - 1]])
            % (v[h[sz - 1]] - v[h[sz - 2]]) > 0) sz--;
            h[sz++] = i;
        }
        h.resize(sz);
        layer.pb(vector<PT>());
        for (int i : h) {
            layer.back().pb(v[i]);
            taken[i] = true;
            cnt++;
        }
    }
    return layer;
}