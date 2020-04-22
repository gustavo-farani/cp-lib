#include "../../../template.cpp"

struct PrimalityTest {
    vector<bool> sieve;
    PrimalityTest (int n) : sieve(n + 1, true) {
        sieve[1] = false;
        for (int i = 2; i <= n; i++) {
            if (sieve[i]) {
                for (ll j = (ll) i*i; j <= n; j += i) {
                    sieve[j] = false;
                }
            }
        }
    }
    bool operator() (int x) { return sieve[x]; }
} prime(1e6);