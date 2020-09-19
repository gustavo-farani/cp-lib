#include "../../boilerplate.cpp"

const int SIGMA = 26;

int getID (char c) { return c - 'a'; }

template<class S>
struct KMP {
    int n;
    vector<vi> dfa;
    KMP (const S& s) : n(s.size()), dfa(n + 1, vi(SIGMA)) {
        dfa[0][getID(s[0])] = 1;
        int k = 0;
        for (int i = 1; i <= n; i++) {
            copy(dfa[k].begin(), dfa[k].end(), dfa[i].begin());
            if (i < n) {
                int j = getID(s[i]);
                dfa[i][j] = i + 1;
                k = dfa[k][j];
            }
        }
    }
    // start == false:
    // all indices i such that t[i-n+1...i] == s
    // start == true:
    // all indices i such that t[i...i+n-1] == s
    vi match (const S& t, bool start = true) {
        vi ans;
        int cs = 0;
        for (int i = 0; i < t.size(); i++) {
            cs = dfa[cs][getID(t[i])];
            if (cs == n) ans.pb(start ? i - n + 1 : i); 
        }
        return ans;
    }
};