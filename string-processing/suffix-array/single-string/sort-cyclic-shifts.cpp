#include "../../../boilerplate.cpp"

template<class S>
vi sortCyclicShifts (const S& s) {
    int n = s.size(), m = 1;
    vi sa(n), ord(n), cnt(n), aux(n);
    iota(sa.begin(), sa.end(), 0);
    sort(sa.begin(), sa.end(), [&] (int i, int j) { return s[i] < s[j]; });
    for (int i = 1; i < n; i++) {
        if (s[sa[i]] > s[sa[i - 1]]) m++;
        ord[sa[i]] = m - 1;
    }
    auto mod = [&] (int i) {
        if (i < 0) i += n;
        else if (i >= n) i -= n;
        return i;
    };
    for (int h = 1; h < n && m < n; h <<= 1) {
        for (int i = 0; i < n; i++) aux[i] = mod(sa[i] - h);
        fill(cnt.begin(), cnt.begin() + m, 0);
        for (int i : aux) cnt[ord[aux[i]]]++;
        partial_sum(cnt.begin(), cnt.begin() + m, cnt.begin());
        for (auto it = aux.rbegin(); it != aux.rend(); it++) {
            sa[--cnt[ord[*it]]] = *it;
        }
        m = 1, aux[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            int d = ord[sa[i]] - ord[sa[i - 1]];
            if (d > 0 || d == 0
            && ord[mod(sa[i] + h)] > ord[mod(sa[i - 1] + h)]) m++;
            aux[sa[i]] = m - 1;
        }
        ord.swap(aux);
    }
    /*this ultimate sorting ensures that, if cyclics shifts
    starting at i and j compare equal to each other,
    with i < j, than i comes before j in sa*/
    sort(sa.begin(), sa.end(), [&] (int i, int j) {
        return ord[i] == ord[j] ? i < j : ord[i] < ord[j];
    });
    return sa;
}