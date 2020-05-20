#include "analytical-formula.cpp"

// v: expansion of x in numerical base p
// v[0] + v[1]*p + v[2]*p^2 + ... 
// + v[k]*p^k = x, with 0 <= v[i] < p
vi radixChange (ll n, int p) {
    vi v;
    while (n > 0) {
        v.pb(n % p);
        n /= p;
    }
    return v;
}

// m, n: large non-negative integers
// MOD: must be prime
// computes (m picks n) mod MOD, decomposing it into a product
// of factors u[i] picks v[i], with 0 <= u[i], v[i] < MOD
MB lucas (ll m, ll n) {  // TO BE TESTED
    vi u(radixChange(m, MOD)), v(radixChange(n, MOD));
    int k = max(u.size(), v.size());
    u.resize(k), v.resize(k);
    MB ans = 1;
    for (int i = 0; i < k; i++) {
        if (u[i] < v[i]) ans = 0; // corolary of Lucas's Theorem
        else ans *= combinations(u[i], v[i]);
    }
    return ans;
}