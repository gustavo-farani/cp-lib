#include "primitive-root.cpp"
#include "baby-step-giant-step.cpp"

// p: prime number
// finds all possible solutions for x in:
// x^k = a (mod p)
vi discreteRoot (int k, int a, int p) {
    vi ans;
    if (a == 0) {
        ans.pb(0);
    } else {
        int g = primitiveRoot(p, true);
        int y = discreteLog(1, modExp(g, k, p), a, p);
        int r = (p - 1)/gcd(p - 1, k);  // C++17 only
        for (int i = y % r; i < p - 1; i += r) {
            ans.pb(modExp(g, i, p));
        }
    }
    return ans;
}