#include "modular.cpp"
#include "../number-theory/trial-division/totient-function.cpp"

// represents an intangible number,
// defined by an exponentiation chain of the form:
// a[k-1]**(a[k-2]**(... a[2]**(a[1]**a[0])))
struct ExponentiationChain {
    int n;
    ExponentiationChain (int n) : n(n) {}
    // let this exponentiation chain to be of the form: a^n
    // return: n as a long long, if n is small enough
    // throws: n as an ExponentiationChain itself, if n is too big
    // WARNING: the exponent n CAN'T become too small, because
    // for the recursion to be correct, it must hold: n >= lg(m)
    // thus, as soon as n fits in a long long, it MUST be returned immediataly
    ll getExponent () {
        switch (n) {
            case 1:
            case 2:
            case 3:
                return n - 1;
            case 4:
                return 9;
            case 5:
                return 262144;
            default:
                throw ExponentiationChain(n - 1);
        }
    }
    // let this exponentiation chain to be of the form: a^n
    // return: a % m
    int getBase (int m) { return n % m; }
    // computes the result of this exponentiation chain, modulo m
    // complexity: O(sqrt(m)*lg(m))
    int mod (int m) {
        if (m == 1) {
            return 0;
        } else {
            int a = getBase(m);
            try {
                return modExp(a, getExponent(), m);
            } catch (ExponentiationChain e) {
                int k = phi(m);
                return modExp(a, k + e.mod(k), m);
            }
        }
    }
};
// NOTE: this particular implementation solves the problem:
// https://open.kattis.com/problems/exponial