#include "prefix-function.cpp"

template<class S>
vi prefixFrequencies (const S& s) {
    int n = s.size();
    vi freq(s.size() + 1);
    vi pi(prefixFunction(s));
    for (int i = 0; i < n; i++) {
        freq[pi[i]]++;
    }
    for (int j = n - 1; j > 0; j--) {
        freq[pi[j - 1]] += freq[j];
    }
    for (int j = 0; j <= n; j++) {
        freq[j]++;
    }
    return freq;
}

template<class S>
vi prefixFrequencies (const S& s, const S& t) {
    int n = s.size(), m = t.size();
    vi pi(prefixFunction(s));
    vi freq(n + 1);
    int prev = 0;
    for (int i = 0; i < m; i++) {
        int j = prev;
        while (j > 0 && t[i] != s[j]) {
            j = pi[j - 1];
        }
        int cur = (t[i] == s[j] ? j + 1 : 0);
        freq[cur]++;
        prev = (cur == n ? pi[n - 1] : cur);
    }
    for (int j = n; j > 0; j--) {
        freq[pi[j - 1]] += freq[j];
    }
    return freq;
}