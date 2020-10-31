#include "../../boilerplate.cpp"

const int MOD = 1e9 + 7;

struct MB {
    int x;
    // implicit conversion in assignment statements
    MB (int x = 0) : x(x < 0 ? x + MOD : x) {}
    MB operator+ (const MB& o) const {
        int y = x + o.x;
        return y >= MOD ? y - MOD : y;
    }
    MB operator- (const MB& o) const {
        int y = x + MOD - o.x;
        return y >= MOD ? y - MOD : y;
    }
    MB operator* (const MB& o) const { return (ll) x*o.x % MOD; }
    void operator+= (const MB& o) { *this = *this + o; }
    void operator-= (const MB& o) { *this = *this - o; }
    void operator*= (const MB& o) { *this = *this*o; }
    operator int() { return x; }  // direct comparisons to int values
    friend ostream& operator<< (ostream& os, MB& o) { return os << o.x; }
    friend istream& operator>> (istream& is, MB& o) { return is >> o.x; }
};