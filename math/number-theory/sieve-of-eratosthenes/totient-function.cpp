#include "../../../template.cpp"

struct Totient {
    vi num, den;
    Totient (int n) : num(n + 1, 1), den(n + 1, 1) {
        for (int i = 2; i <= n; i++) {
            if (den[i] == 1) {
                for (int j = i; j <= n; j += i) {
                    num[j] *= i - 1;
                    den[j] *= i;
                }
            }
        }
    }
    int operator() (int n) { return n*num[n]/den[n]; }
};