#include "../mod-base.cpp"

// computes factorials <= N and their modular inverses
// assumes MOD is prime
// time complexity: O(N)

const int N = 1e6;

MB num[N + 1], den[N + 1];

void build () {
    static MB inv[N + 1];
    num[0] = num[1] = den[0] = den[1] = inv[1] = 1;
    for (int i = 2; i <= N; i++) {
        inv[i] = inv[MOD % i]*MB(-(MOD/i));
        num[i] = num[i - 1]*MB(i);
        den[i] = den[i - 1]*inv[i];
    }
}