#include "longest-common-prefix-array.cpp"

template<class S>
ll countDistinctSubstrings (const S& s) {
    ll n = s.size();
    vi lcp = longestCommonPrefixArray(s);
    return n*(n + 1)/2 - accumulate(lcp.begin(), lcp.end(), 0LL);
}