#include <iostream>
#include "fast-exponentiation.cpp"
using namespace std;

typedef long long ll;
int MOD;
    
struct MB {
    int x;
    MB (int x = 0) : x(x) {}  // implicit conversion in assignment statements
    MB operator+ (MB o) {
        int y = x + o.x;
        return y >= MOD ? y - MOD : y;
    }
    MB operator- (MB o) {
        int y = x + MOD - o.x;
        return y >= MOD ? y - MOD : y;
    }
    MB operator* (MB o) { return (ll) x*o.x % MOD; }
    MB operator/ (MB o) { return *this*fExp(o, MOD - 2); }
    operator int() { return x; }  // direct comparisons to int values
};

istream& operator>> (istream& is, MB& m) { is >> m.x; }  // reading easily