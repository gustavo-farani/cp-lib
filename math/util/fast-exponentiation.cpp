#include "../../template.cpp"

template <class T>
T fastExp (T a, ll n) {
    T ans(1);
    while (n) {
        if (n & 1) ans = ans * a;
        a = a * a;
        n >>= 1;
    }
    return ans;
}