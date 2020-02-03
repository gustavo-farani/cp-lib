#include <vector>
using namespace std;

typedef vector<int> vi;

struct Quantifier {
    bool b;   // b = 0 for 0-based, b = 1 for 1-based (indexation)
    vi pref;
    Quantifier (int n, bool b) : pref(n + 1), b(b) {}
    int& operator[] (int i) {
        return pref[i + 1 - b];
    }
    void build (int n) {
        for (int i = 1; i <= n; i++) {
            pref[i] += pref[i - 1];
        }
    }
    int count (int l, int r) {
        return pref[r + 1 - b] - pref[l - b];
    }
    bool all (int l, int r) {
        return (count(l, r) == r - l + 1);
    }
    bool any (int l, int r) {
        return (count(l, r) > 0);
    }
    bool none (int l, int r) {
        return (count(l, r) == 0);
    }
};