#include "factorial.cpp"

// number of ways to map n keys
// to m possible values such that
// no two keys are assigned the same value
MB injections (int n, int m) {
    if (m < n) {
        return 0;
    } else {
        return num[m]*den[m - n];
    }
}

// number of subsets with exactly k elements
// from a set with n elements
MB subsets (int n, int k) {
    if (k > n) {
        return 0;
    } else {
        return num[n]*den[n - k]*den[k];
    }
}

// number of non-negative solutions for equation:
// x1 + ... + xn = k
// n := number of variables / number of classes
// k := independent term / number of instances
MB solutions (int n, int k) {
    return subsets(n + k - 1, k);
}