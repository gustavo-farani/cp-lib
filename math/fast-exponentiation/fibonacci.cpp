#include "../number-theory/modular-arithmetic/mod-base.cpp"

// SQRT5: discrete square root of 5, mod MOD
// this should be a constant determined in compile-time
// you can pre-compute this in a separate program,
// calling discreteRoot(2, 5, MOD)
// NOTE: discrete square root of 5 might not exist for given MOD
template<int SQRT5>
struct Fibonacci {
    const MB O = 1, T = 2, F = 5, S = SQRT5;
    MB a, b, c, sq;
    Fibonacci () : a((O + S)/T), b((O - S)/T), c(S/F) {}
    MB operator() (int n) {
        return c*(fastExp(a, n) - fastExp(b, n));
    }
};

// sample problem: https://codeforces.com/problemset/problem/446/C