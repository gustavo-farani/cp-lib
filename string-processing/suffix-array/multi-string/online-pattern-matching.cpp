#include "sort-suffixes.cpp"
#include "../../../problem-solving-paradigms/binary-search/monotonically-increasing.cpp"

struct PatternMatching {
    int n;
    vector<string> v;
    vector<ii> sa;
    PatternMatching (vector<string>&& v, vector<ii>&& sa) :
        n(sa.size()), v(v), sa(sa)
    {}
    int comp (int k, const string& s) {
        auto mis = mismatch(s.begin(), s.end(), v[sa[k].fi].begin() + sa[k].se);
        if (mis.fi == s.end()) {
            return 0;
        } else if (mis.se == v[sa[k].fi].end()) {
            return -1;
        } else {
            return *mis.se - *mis.fi;
        }
    }
    ii match (const string& s) {
        int first = search(0, n - 1, [&] (int k) { return comp(k, s) >= 0; });
        int last = search(0, n - 1, [&] (int k) { return comp(k, s) > 0; });
        return ii(first, last);
    }
};