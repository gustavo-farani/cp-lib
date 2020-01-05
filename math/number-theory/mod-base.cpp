#include "../fast-exponentiation.cpp"

typedef long long ll;
int MOD;    // it is suitable to use MOD as a global variable/constant

struct modBase {
    int val;
    modBase (int val) : val(val) {}
    modBase operator+ (modBase o) {
        int ans = val + o.val;
        if (ans >= MOD) ans -= MOD;
        return ans;
    }
    modBase operator- (modBase o) {
        int ans = val + MOD - o.val;
        if (ans >= MOD) ans -= MOD;
        return ans;
    }
    modBase operator* (modBase o) {
        return (ll) val * o.val % MOD;
    }
    modBase operator/ (modBase o) {
        return *this * fExp(o, MOD - 2);
    }
};