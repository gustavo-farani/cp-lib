#include "../../../boilerplate.cpp"

template<class T>
vector<T> factorization (T n) {
    vector<T> ans;
    for (T d = 2; d*d <= n; d++) {
        while (n % d == 0) {
            n /= d;
            ans.pb(d);
        }
    }
    if (n > 1) ans.pb(n);
    return ans;
}