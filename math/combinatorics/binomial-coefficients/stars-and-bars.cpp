#include "analytical-formula.cpp"

// number of non-negative solutions for equation:
// x1 + ... + xn = k
// n := number of variables / number of classes
// k := independent term / number of instances
MB solutions (int n, int k) {
    return combinations(n + k - 1, k);
}