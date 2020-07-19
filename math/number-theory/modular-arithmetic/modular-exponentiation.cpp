#include "mod-base.cpp"
#include "../trial-division/totient-function.cpp"

// Trick for computing (a ^ n) mod m
// NOTE: assumes n >= log2(m)
int modExp (int a, int n, int m) {
    int d = phi(m), r = n % d;
    MOD = m;  // TODO set MOD not as constant
    return fastExp(MB(a), d + r);
}