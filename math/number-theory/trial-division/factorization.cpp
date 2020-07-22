#include "../../../boilerplate.cpp"

vector<ll> factorization (ll n) {
    vector<ll> ans;
    for (ll d = 2; d*d <= n; d++) {
        while (n % d == 0) {
            n /= d;
            ans.pb(d);
        }
    }
    if (n > 1) ans.pb(n);
    return ans;
}