#include "extended-euclidean-algorithm.cpp"

typedef long long ll;
typedef pair<ll, ll> pll;

ll mod (ll a, ll m) {
    return (((a % m) + m) % m);
}

pll paramSol (ll a, ll b, ll x0, ll y0, ll t) {
    // X = X0 + bt
    // Y = Y0 - at
    return {x0 + b*t, y0 - a*t};
}

pll positiveBounds (ll a, ll b, ll x0, ll y0) {
    // x = x0 + bt
    ll inf = (mod(x0, b) - x0)/b;
    // y = y0 - at
    ll sup = (y0 - mod(y0, a))/a;
    return {inf, sup};
}

pll solve (ll a, ll b, ll c) {
    ll m, n;
    ll g = eea(a, b, m, n);
    if (c % g == 0) {
        ll x0 = m*(c/g);
        ll y0 = n*(c/g);
        a /= g;
        b /= g;
        ll inf, sup;
        tie(inf, sup) = positiveBounds(a, b, x0, y0);
        if (inf <= sup) {
            return paramSol(a, b, x0, y0, inf);
        } else {
            throw -1;  // no solution
        }
    } else {
        throw -1;  // independent term must be multiple of gcd
    }
}