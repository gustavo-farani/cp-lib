#include "prefix-function.cpp"
#include <deque>
#include <algorithm>
using namespace std;

typedef long long ll;

template <class S>
ll countSubstrings (const S& s) {
    int n = s.size();
    deque<class S::value_type> t;
    ll total = 0;
    for (int i = 0; i < n; i++) {
        t.push_front(s[i]);
        vi pi(prefixFunction(t));
        int j = *max_element(pi.begin(), pi.end());
        total += t.size() - j;
    }
    return total;
}