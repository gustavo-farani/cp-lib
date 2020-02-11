#include <vector>
#include "prefix-function.cpp"
using namespace std;

typedef vector<int> vi;
#define pb push_back

template<class S>
vector<bool> patternMatching (const S& s, const S& t) {
    int n = s.size(), m = t.size();
    vector<bool> pos(m);
    vi pi(prefixFunction(s));
    int prev = 0;
    for (int i = 0; i < m; i++) {
        int j = prev;
        while (j > 0 && t[i] != s[j]) {
            j = pi[j - 1];
        }
        int cur = (t[i] == s[j] ? j + 1 : 0);
        pos[i] = (cur == n);
        prev = (cur == n ? pi[n - 1] : cur);
    }
    /*
    Default: match at ending positions
        pos[i] = (t.substr(i - n + 1, n) == s)
    Custom: match at starting positions
        pos[i] = (t.substr(i, n) == s)
    To obtain the custom version, uncomment the for loop above,
    and let it run just before the function returns

    for (int i = 0; i + n <= m; i++) {
        pos[i] = pos[i + n - 1];
    }
    */
    return pos;
}