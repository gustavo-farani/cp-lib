#include "binomial-coefficient.cpp"
#include "../util/mod-base.cpp"

// number of non-negative solutions for linear equation:
// x1 + ... + xn = k
// n := number of variables / number of classes
// k := independent term / number of instances
ModBase starsAndBars (int n, int k) {
    return combinations(n + k - 1, k);
}