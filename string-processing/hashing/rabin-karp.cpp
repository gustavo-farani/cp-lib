#include "../../math/number-theory/modular-arithmetic/mod-base.cpp"

random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> gen('z' + 1, 1e8);
unsigned long long base1 = (gen(mt) << 1) + 1;
MB base2 = (gen(mt) << 1) + 1;

struct RabinKarp {
    vector<unsigned long long> p1, pref1;
    vector<MB> p2, pref2;
    RabinKarp (const string& s, int n) :
        p1(n + 1, 1), pref1(n + 1), p2(n + 1, 1), pref2(n + 1)
    {
        for (int k = 0; k < n; k++) {
            p1[k + 1] = base1*p1[k];
            p2[k + 1] = base2*p2[k];
        }
        for (int k = 0; k < n; k++) {
            pref1[k + 1] = base1*pref1[k] + s[k];
            pref2[k + 1] = base2*pref2[k] + MB(s[k]);
        }
    }
    unsigned long long hash1 (int i, int len) {
        return pref1[i + len] - pref1[i]*p1[len];
    }
    MB hash2 (int i, int len) {
        return pref2[i + len] - pref2[i]*p2[len];
    }
    bool equal (int i, int j, int len) {
        return hash1(i, len) == hash1(j, len)
        && hash2(i, len) == hash2(j, len);
    }
};