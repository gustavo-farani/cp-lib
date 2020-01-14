typedef long long ll;

template <class T>
T fExp (T &a, ll n) {
    T ans(1);
    while (n) {
        if (n & 1) ans = ans * a;
        a = a * a;
        n >>= 1;
    }
    return ans;
}

// NOTE: referenced parameter 'a' will be modified