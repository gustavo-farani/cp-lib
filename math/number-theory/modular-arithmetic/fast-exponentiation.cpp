#include "../../../template.cpp"

template<class T>
T fastExp (T a, ll n) {
    T ans(1);
    while (n) {
        if (n & 1) ans = ans * a;
        a = a * a;
        n >>= 1;
    }
    return ans;
}

#include "mod-base.cpp"
#include "../factorization/totient-function.cpp"

// Trick for computing (a ^ n) mod m
// NOTE: assumes n >= log2(m)
int modExp (int a, int n, int m) {
    int d = phi(m), r = n % d;
    MOD = m;
    return fastExp(MB(a), d + r);
}