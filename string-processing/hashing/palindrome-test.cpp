#include <string>
#include <algorithm>
#include "rabin-karp.cpp"
using namespace std;

struct PalindromeTest {
    int n;
    RabinKarp dir;
    RabinKarp inv;
    PalindromeTest (const string &s) :
        n(s.length()), dir(n), inv(n)
    {
        string t(s);
        dir.build(t);
        reverse(t.begin(), t.end());
        inv.build(t);
    }
    bool operator() (int i, int len) {
        int j = n - i - len;
        if (dir.hash1(i, len) == inv.hash1(j, len)
        && dir.hash2(i, len) == inv.hash2(j, len)) {
            return true;
        } else {
            return false;
        }
    }
};