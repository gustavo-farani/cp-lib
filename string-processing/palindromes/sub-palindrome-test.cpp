#include "manacher.cpp"

struct SubPalindromeTest {
    array<vi, 2> d;
    template<class S> SubPalindromeTest (const S& s) : d(manacher(s)) {}
    bool operator() (int i, int len) {
        bool z = len & 1;
        return d[z][i + (len >> 1)] >= len + z >> 1;
    }
};