#include "../../template.cpp"

typedef unsigned long long ull;
 
const ll MOD = exp2(31) - 1;
 
random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> gen('z' + 1, 1e8);
ll point = (gen(mt) << 1) + 1;
 
struct RabinKarp {
	vector<ull> p1, pref1;
	vector<ll> p2, pref2;
	RabinKarp (int n) :
        p1(n + 1), pref1(n + 1),
        p2(n + 1), pref2(n + 1)
    {}
    void build (const string& s) {
        int n = s.length();
        p1[0] = p2[0] = 1;
		for (int k = 0; k < n; k++) {
			p1[k + 1] = point*p1[k];
			p2[k + 1] = point*p2[k] % MOD;
		}
		pref1[0] = pref2[0] = 0;
		for (int k = 0; k < n; k++) {
			pref1[k + 1] = point*pref1[k] + s[k];
			pref2[k + 1] = (point*pref2[k] + s[k]) % MOD;
		}
    }
	ull hash1(int i, int len) {
		return pref1[i + len] - pref1[i]*p1[len];
	}
	ll hash2(int i, int len) {
		return ((((pref2[i + len] - pref2[i]*p2[len]) % MOD) + MOD) % MOD);
	}
};