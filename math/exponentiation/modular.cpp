#include "../../boilerplate.cpp"

// computes a**n mod m
// assumes 0 <= a < m
// complexity: O(lg n)
// NOTE: a and m can't be long long for overflow reasons
int modExp (int a, ll n, int m) {
    int ans = 1;
    while (n) {
        if (n & 1) ans = (ll) ans*a % m;
        a = (ll) a*a % m;
        n >>= 1;
    }
    return ans;
}