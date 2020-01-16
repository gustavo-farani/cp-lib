#include "fast-exponentiation.cpp"

typedef long long ll;
int MOD;    // it is suitable to use MOD as a global variable/constant

struct ModBase {
    int val;
    ModBase (int val) : val(val) {}
    ModBase operator+ (ModBase o) {
        int ans = val + o.val;
        if (ans >= MOD) ans -= MOD;
        return ans;
    }
    ModBase operator- (ModBase o) {
        int ans = val + MOD - o.val;
        if (ans >= MOD) ans -= MOD;
        return ans;
    }
    ModBase operator* (ModBase o) {
        return (ll) val * o.val % MOD;
    }
    ModBase operator/ (ModBase o) {
        return *this * fExp(o, MOD - 2);
    }
};