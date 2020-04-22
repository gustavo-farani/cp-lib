#include "../number-theory/modular-arithmetic/mod-base.cpp"

MB combinations (int n, int k) {
    k = min(n - k, k);
    MB num(1), den(1);
    for (int i = 1; i <= k; i++) {
        num *= n + 1 - i;
        den *= i;
    }
    return num/den;
}