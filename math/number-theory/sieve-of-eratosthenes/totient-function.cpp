#include "../../../template.cpp"

struct Totient {
    vector<ll> num, den;
    Totient (int lim) : num(lim + 1), den(lim + 1) {
        for (int i = 1; i <= lim; i++) num[i] = den[i] = 1;
        for (int i = 2; i <= lim; i++) {
            if (den[i] == 1LL) {
                for (int j = i; j <= lim; j += i) {
                    num[j] *= i - 1;
                    den[j] *= i;
                }
            }
        }
    }
    ll operator() (int n) { return n*num[n]/den[n]; }
};