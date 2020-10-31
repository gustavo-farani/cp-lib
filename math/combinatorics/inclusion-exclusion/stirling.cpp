#include "../../fast-exponentiation/generic.cpp"
#include "../binomial-coefficients/combinations.cpp"

// number of ways to split a set of n labeled
// elements into exactly k non-labeled equivalence classes
MB partitions (int n, int k) {
    MB ans = 0;
    for (int i = 0; i <= k; i++) {
        MB aux = subsets(k, i)*fastExp(MB(k - i), n);
        if (i & 1) ans -= aux;
        else ans += aux; 
    }
    ans *= den[k];
    return ans;
}

// number of ways to map n keys
// to m possible values such that
// each value has at least one key assigned to it
MB surjections (int n, int m) {
    if (n < m) {
        return 0;
    } else {
        return partitions(n, m)*num[m];
    }
}