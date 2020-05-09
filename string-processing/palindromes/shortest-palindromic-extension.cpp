#include "manacher.cpp"

template<class S>
S shortestPalindromicExtension (const S& s) {
    int n = s.size(), last = n;
    auto d = manacher(s);
    for (int i = 0; i < n; i++) {
        if (i + d[0][i] == n) last = min(last, i - d[0][i]);
    }
    for (int i = 0; i < n; i++) {
        if (i + d[1][i] == n) last = min(last, i - d[1][i] + 1);
    }
    S ans(s);
    for (int i = last - 1; i >= 0; i--) ans.pb(s[i]);
    return ans;
}