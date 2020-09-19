#include "../../number-theory/sieve-of-eratosthenes/totient-function.cpp"
#include "../mod-base.cpp"
#include "../../number-theory/divisors/find-divisors.cpp"

Totient phi(1e6);

// n: number of positions in each cycle
// k: number of possible values in each position
// application of polya's enumeration theorem
// when invariant permutations are exactly the n cyclic shifts
// NOTE: reversed cyclic shifts are NOT considered invariant permutations
MB necklaces (int n, ll k) {  // TO BE TESTED
    MB sum = 0;
    divisors(n, [&] (int d) { sum += fastExp(k, d)*MB(phi(n/d)); });
    return sum/MB(n);
}