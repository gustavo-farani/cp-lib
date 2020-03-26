#include <string>
using namespace std;

typedef long long ll;

/* r: (representation) string representation of floating-point
number to be converted. It can either have a decimal point or not. */
/* p: (precision) maximum number of decimal positions after the decimal
point in r */
ll scale (const string& r, int p) {  // credits to josecruz
    ll ans = 0LL;
    int i = 0;
    while (i < r.size() && r[i] != '.') {
        ans *= 10LL;
        ans += r[i++] - '0';
    }
    int j = 0;
    while (++i < r.size()) {
        ans *= 10LL;
        ans += r[i] - '0';
        j++;
    }
    while (j++ < p) ans *= 10LL;
    return ans;
}

/* shorter alternative: (it is not sure that will work)
#include <cmath>

ll scale (double x, int p) {
    return llrint(pow(10.0, p)*x);
} */