#include "../../../template.cpp"

// sa: suffix array of string s
// lcp[i]: length of the longest common prefix between
// suffixes starting at indices sa[i] and sa[i + 1]
template<class S>
vi longestCommonPrefixArray (const S& s) {
    int n = s.size(), m = 1, len = 0;
    vi sa(n), ord(n), cnt(n), aux(n), lcp(n);
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
    // after suffix array sa is computed, run Kasai's Algorithm
    // to find the longest common prefix array
    for (int i = 0; i < n; i++) {
        if (ord[i] == n - 1) {
            len = 0;
        } else {
            int j = sa[ord[i] + 1];
            while (i + len < n && j + len < n
            && s[i + len] == s[j + len]) len++;
            lcp[ord[i]] = len;
            if (len > 0) len--;
        }
    }
    return lcp;
}