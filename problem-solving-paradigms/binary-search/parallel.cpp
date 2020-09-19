#include "../../boilerplate.cpp"

// monotonically decreasing
struct Search {
    int id, l, r, m;
    Search (int id, int l, int r) :
        id(id), l(l), r(r + 1), m(l + r + 1 >> 1)
    {}
    bool operator< (const Search& o) const {
        return m < o.m;
    }
    void split (bool success) {
        if (success) l = m;
        else r = m;
        m = l + r >> 1;
    }
    bool finished () { return r - l <= 1; }
    int result () { return l; }
};

// monotonically increasing
struct Search {
    int id, l, r, m;
    Search (int id, int l, int r) :
        id(id), l(l), r(r), m(l + r >> 1)
    {}
    bool operator< (const Search& o) const {
        return m < o.m;
    }
    void split (bool success) {
        if (success) r = m;
        else l = m + 1;
        m = l + r >> 1;
    }
    bool finished () { return l == r; }
    int result () { return l; }
};

// T: weight of events in e, which follow an increasing order
// U: tuple with parameters for each update event
// Q: tuple with parameters for each query
template<class T, class U, class Q>
vector<T> solve (vector<Q>& q, const vector<pair<T, U>>& e) {
    vector<pair<Search, Q>> p;
    for (int i = 0; i < q.size(); i++) {
        p.emplace_back(Search(i, 0, e.size() - 1), q[i]);
    }
    vector<T> ans(q.size());
    while (!p.empty()) {
        sort(p.begin(), p.end());
        // TODO clear data structure
        vector<pair<Search, Q>> aux;
        int cur = 0;
        for (auto [s, qry] : p) {
            if (s.finished()) {
                ans[s.id] = e[s.result()].first;
            } else {
                while (cur < e.size() && cur <= s.m) {
                    // TODO update data structure passing
                    // e[cur].second as parameters
                    cur++;
                }
                // TODO query data structure passing
                // qry as parameters and determine success
                bool sucess;
                s.split(sucess);
                aux.emplace_back(s, qry);
            }
        }
        p.swap(aux);
    }
    return ans;
}