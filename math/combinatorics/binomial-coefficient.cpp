#include <algorithm>
#include "../util/mod-base.cpp"
using namespace std;

ModBase combinations (int n, int k) {
    k = min(n - k, k);
    ModBase num(1), den(1);
    for (int i = 1; i <= k; i++) {
        num = num * ModBase(n + 1 - i);
        den = den * ModBase(i);
    }
    return num/den;
}