#include "../trial-division/factorization.cpp"
#include "../trial-division/totient-function.cpp"
#include "../../fast-exponentiation/modular.cpp"

// computes a generator/primitive root mod m
// it is a number g such that, for all n with gcd(n, m) == 1, 
// there is a discrete logarithm k such that g^k = n (mod m)
// if m is prime, the algorithm will run faster
// throws -1, if a generator mod m does not exist
int primitiveRoot (int m, bool prime) {
    int n = prime ? m - 1 : phi(m);
    vi p = factorization(n);
    for (int g = 1; g < m; g++) {
        bool ok = prime || modExp(g, n, m) == 1;
        for (int i = 0; ok && i < p.size(); i++) {
            ok &= modExp(g, n/p[i], m) != 1;
        }
        if (ok) return g;
    }
    throw -1;
}