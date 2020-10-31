#include "../mod-base.cpp"

// number of subsets with exactly k elements
// from a set with n elements

template<class T>
T subsets (int n, int k) {
    k = min(n - k, k);
    T num = 1, den = 1;
    for (int i = 1; i <= k; i++) {
        num *= n + 1 - i;
        den *= i;
    }
    return num/den;
}