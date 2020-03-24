#include <tuple>
#include <numeric>
#include "../point.cpp"
using namespace std;

struct Line {
    ll a, b, c;
    Line (const PT& p, const PT& q) {  // credits to josecruz
        PT v = q - p;
        a = v.y, b = -v.x, c = p ^ q;
        ll g = gcd(gcd(a, b), c);  // C++ 17 only
        if (a < 0LL || a == 0LL && b < 0LL) g = -g;
        a /= g, b /= g, c /= g;
    }
    bool touches (const PT& p) {
        return PT{a, b}*p == c;
    }
};