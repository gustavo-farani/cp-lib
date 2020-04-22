#include "../../../template.cpp"

vector<ll> find (ll n) {
    vector<ll> d;
    ll i;
    for (i = 1; i*i < n; i++) {
        if (n % i == 0) {
            d.pb(i);
            d.pb(n/i);
        }
    }
    if (i*i == n) d.pb(i);
    return d;
}