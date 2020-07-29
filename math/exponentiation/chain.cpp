#include "modular.cpp"
#include "../number-theory/trial-division/totient-function.cpp"

// represents an intangible number,
// defined by an exponentiation chain of the form:
// a[k-1]**(a[k-2]**(... a[2]**(a[1]**a[0])))
struct ExponentiationChain {
    int n;
    ExponentiationChain (int n) : n(n) {}
    // let this exponentiation chain to be of the form: a^n
    // it tests if n fits a long long
    bool smallExponent () {
        return n <= 5;
    }
    // let this exponentiation chain to be of the form: a^n
    // return: n as a long long, if n is small enough
    // WARNING: the exponent n CAN'T become too small, because
    // for the recursion to be correct, it must hold: n >= lg(m)
    // thus, as soon as n fits in a long long, it MUST be returned immediataly
    ll getExponent () {
        ll ans;
        switch (n) {
            case 1:
            case 2:
            case 3:
                ans = n - 1;
            break;
            case 4:
                ans = 9;
            break;
            case 5:
                ans = 262144;
            break;
        }
        return ans;
    }
    // let this exponentiation chain to be of the form: a^n
    // return: n as an ExponentiationChain itself, if n is too big
    ExponentiationChain next () { return n - 1; }
    // let this exponentiation chain to be of the form: a^n
    // return: a % m
    int getBase (int m) { return n % m; }
    // computes the result of this exponentiation chain, modulo m
    // complexity: O(lg(m)(T + lg(m))), where
    // T = time complexity for each call to euler totient function
    int mod (int m) {
        if (m == 1) {
            return 0;
        } else {
            int a = getBase(m);
            if (smallExponent()) {
                return modExp(a, getExponent(), m);
            } else {
                int k = phi(m);
                return modExp(a, k + next().mod(k), m);
            }
        }
    }
};
// NOTE: this particular implementation solves the problem:
// https://open.kattis.com/problems/exponial