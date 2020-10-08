#include "../../../boilerplate.cpp"

// Baby-Step-Giant-Step Algorithm for Discrete Logarithm
// finds the minimum non-negative value x such that
// k*a**x == b (mod m)
// throws -1 if there is no solution for x
// assumes 0 <= k, a, b < m
int discreteLog (int k, int a, int b, int m) {
    if (a == 0) {
        if (b == 0) return 1;  // assumes 0^0 is undefined
        else throw -1;
    } else {
        int cnt = 0, g;
        while ((g = gcd(a, m)) > 1) {  // C++17 only
            if (b == k) return cnt;
            if (b % g != 0) throw -1;
            b /= g, m /= g, ++cnt;
            k = (ll) k*a / g % m;
        }
        int n = sqrt(m) + 1, giant = 1;
        for (int i = 0; i < n; ++i) giant = (ll) giant*a % m;
        map<int, int> meet;
        for (int q = 0, cur = b; q <= n; ++q) {
            meet[cur] = q;
            cur = (ll) cur*a % m;
        }
        for (int p = 1, cur = k; p <= n; ++p) {
            cur = (ll) cur*giant % m;
            auto it = meet.find(cur);
            if (it != meet.end()) {
                return n*p - it->se + cnt;
            }
        }
        throw -1;
    }
}