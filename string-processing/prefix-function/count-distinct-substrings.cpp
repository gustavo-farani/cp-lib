#include "prefix-function.cpp"

template <class S>
ll countSubstrings (const S& s) {  // complexity: O(n^2)
    int n = s.size();
    S t;
    ll total = 0;
    for (int i = 0; i < n; i++) {
        t.pb(s[i]);
        reverse(t.begin(), t.end());
        vi pi(prefixFunction(t));
        reverse(t.begin(), t.end());
        int j = *max_element(pi.begin(), pi.end());
        total += t.size() - j;
    }
    return total;
}