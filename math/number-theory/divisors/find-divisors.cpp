#include "../../../template.cpp"

template<class F>
void divisors (ll n, F get) {
    ll i = 1;
    while (i*i < n) {
        if (n % i == 0) {
            get(i);
            get(n/i);
        }
        i++;
    }
    if (i*i == n) get(i);
}