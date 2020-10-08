#include "../../../boilerplate.cpp"

// v: vector of strings
// sorts lexicographically the suffixes from all the strings,
// at a time complexity of O(n lg^2 n)
// returns sa: the multi-string suffix array,
// a succession of pairs (i, j), representing the suffix of the
// ith string in v with starting position j
template<class S>
vector<ii> sortSuffixes (vector<S>& v) {
    vector<ii> sa;
    int lim = 0, h = 1, m = 1;
    vector<vi> ord, aux;
    for (int i = 0; i < v.size(); i++) {
        int sz = v[i].size();
        lim = max(lim, sz);
        ord.emplace_back(sz + 1, -1);
        aux.emplace_back(sz + 1, -1);
        for (int j = 0; j < sz; j++) {
            sa.emplace_back(i, j);
        }
    }
    sort(sa.begin(), sa.end(), [&] (const ii& p, const ii& q) {
        return v[p.fi][p.se] < v[q.fi][q.se];
    });
    ord[sa[0].fi][sa[0].se] = 0;
    for (int i = 1; i < sa.size(); i++) {
        if (v[sa[i - 1].fi][sa[i - 1].se]
        < v[sa[i].fi][sa[i].se]) m++;
        ord[sa[i].fi][sa[i].se] = m - 1;
    }
    auto comp = [&] (const ii& p, const ii& q) {
        return ii(ord[p.fi][p.se],
        ord[p.fi][min(int(v[p.fi].size()), p.se + h)])
        < ii(ord[q.fi][q.se],
        ord[q.fi][min(int(v[q.fi].size()), q.se + h)]);
    };
    while (h < lim) {
        sort(sa.begin(), sa.end(), comp);
        m = 1;
        ord[sa[0].fi][sa[0].se] = 0;
        for (int i = 1; i < sa.size(); i++) {
            if (comp(sa[i - 1], sa[i])) m++;
            aux[sa[i].fi][sa[i].se] = m - 1;
        }
        ord.swap(aux);
        h <<= 1;
    }
    return sa;
}