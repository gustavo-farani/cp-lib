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
        auto mis = mismatch(s.begin(), s.end(), v[sa[k].first].begin() + sa[k].second);
        if (mis.first == s.end()) {
            return 0;
        } else if (mis.second == v[sa[k].first].end()) {
            return -1;
        } else {
            return *mis.second - *mis.first;
        }
    }
    ii match (const string& s) {
        int first = search(0, n - 1, [&] (int k) { return comp(k, s) >= 0; });
        int last = search(0, n - 1, [&] (int k) { return comp(k, s) > 0; });
        return ii(first, last);
    }
};