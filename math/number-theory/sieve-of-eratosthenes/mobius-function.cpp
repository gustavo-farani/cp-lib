#include "../../../boilerplate.cpp"

struct Mobius {
    vi mu;
    Mobius (int n) : mu(n + 1, 1) {
        vector<bool> sieve(n + 1, true);
        for (int i = 2; i <= n; i++) {
            if (sieve[i]) {
                for (int j = i; j <= n; j += i) {
                    mu[j] *= -1;
                    sieve[j] = false;
                }
                ll sq = (ll) i*i;
                for (ll j = sq; j <= n; j += sq) mu[j] = 0;
            }
        }
    }
    int operator() (int n) { return mu[n]; }
} mu(1e5);