#include "../../../data-structures/sparse-table/offline-subarray-minimum-query.cpp"

struct LCP {  // TO BE TESTED
    int n;
    RangeMin<int> st;
    vi ord;
    template<class S>
    LCP (const S& s) : n(s.size()), st(n - 1), ord(n) {
        int m = 1, len = 0;
        vi sa(n), cnt(n), aux(n);
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(), [&] (int i, int j) { return s[i] < s[j]; });
        for (int i = 1; i < n; i++) {
            if (s[sa[i]] > s[sa[i - 1]]) m++;
            ord[sa[i]] = m - 1;
        }
        for (int h = 1; h < n && m < n; h <<= 1) {
            int l = 0, r = h;
            for (int i : sa) {
                if (i >= h) aux[r++] = i - h;
                if (i >= n - h) aux[l++] = i;
            }
            fill(cnt.begin(), cnt.begin() + m, 0);
            for (int i : aux) cnt[ord[i]]++;
            partial_sum(cnt.begin(), cnt.begin() + m, cnt.begin());
            for (auto it = aux.rbegin(); it != aux.rend(); it++) {
                sa[--cnt[ord[*it]]] = *it;
            }
            m = 1, aux[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                int d = ord[sa[i]] - ord[sa[i - 1]];
                if (d > 0 || d == 0 && (sa[i - 1] >= n - h
                || ord[sa[i] + h] > ord[sa[i - 1] + h])) m++;
                aux[sa[i]] = m - 1;
            }
            ord.swap(aux);
        }
        for (int i = 0; i < n; i++) {
            if (ord[i] == n - 1) {
                len = 0;
            } else {
                int j = sa[ord[i] + 1];
                while (i + len < n && j + len < n
                && s[i + len] == s[j + len]) len++;
                st.at(ord[i]) = len;
                if (len > 0) len--;
            }
        }
        st.build(n - 1);
    }
    int query (int i, int j) {
        int l = ord[i], r = ord[j];
        if (l > r) swap(l, r);
        return st.query(l, r - 1);
    }
};