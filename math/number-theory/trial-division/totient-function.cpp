#include "../../../boilerplate.cpp"

template<class T>
T phi (T n) {
    T ans = n;
    for (T i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            do n /= i; while (n % i == 0);
            ans -= ans/i;
        }
    }
    if (n > 1) ans -= ans/n;
    return ans;
}