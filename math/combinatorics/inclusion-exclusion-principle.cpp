#include "mod-base.cpp"

MB countUnion (int n, const function<MB(int)>& countIntersection) {
    MB ans = 0;
    for (int mask = 1; mask < 1 << n; mask++) {
        MB aux = countIntersection(mask);
        if (__builtin_popcount(mask) & 1) {
            ans += aux;
        } else {
            ans -= aux;
        }
    }
    return ans;
}