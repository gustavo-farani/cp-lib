typedef long long ll;

int count (ll n) {
    int total = 0;
    ll i;
    for (i = 1; i*i < n; i++) {
        if (!(n % i)) total += 2;
    }
    return total + (i*i == n);
}