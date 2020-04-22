#include "../../template.cpp"

template<class S>
vi prefixFunction (const S &s) {
    int n = s.size();
    vi pi(n);
    for (int i = 0; i + 1 < n; i++) {
        int j = pi[i];
        while (j > 0 && s[i + 1] != s[j]) {
            j = pi[j - 1];
        }
        pi[i + 1] = (s[i + 1] == s[j] ? j + 1 : 0);
    }
    return pi;
}